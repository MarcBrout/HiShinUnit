//
// Created by 53818 on 27/11/2017.
//

#include <algorithm>
#include "Position.hpp"
#include "TaskManager.hpp"
#include "Logger.hpp"

std::string TaskManager::executeTask(std::string const &task) {
    std::vector<std::string> out;

    splitter.clear();
    splitter.split(task, " ,");
    splitter.moveTokensTo(out);

    std::string proceed;
    if (!out.empty()) {
        if (isBoardInConfiguration) {
            proceed = "CONFIGURE";
        } else {
            proceed = out.front();
            out.erase(out.begin());
        }

        if (tasks.find(proceed) == tasks.end())
            return MSG_UNKNOWN;
        return (*this.*tasks[proceed])(out);
    }
    return MSG_ERROR;
}

std::string TaskManager::start(std::vector<std::string> const &args) {
    if (args.size() != 1)
        return MSG_ERROR + " expecting only board size (18)";

    if (std::stoi(args[0]) != size)
        return MSG_ERROR + " size not supported (18)";

    return MSG_OK;
}

std::string TaskManager::turn(std::vector<std::string> const &args) {
    if (args.size() != 2)
        return MSG_ERROR + " expecting TURN with format TURN [x],[y]";
    auto x = static_cast<uint32_t >(std::stoi(args[0]));
    auto y = static_cast<uint32_t >(std::stoi(args[1]));

    if ((x < 0 || x > size) || (y < 0 || y > size))
        return MSG_ERROR + " expecting x and y in range 0..18";
    (*board).setCellState(y, x, Player2);

    Position pos;
    //TODO Guess POS IA
    getIaPlay(pos);
    (*board).setCellState(pos.y, pos.x, Player1);
    return pos.toString();
}

std::string TaskManager::begin(std::vector<std::string> const &args) {
    Position pos;
    //TODO Guess POS IA
    getIaPlay(pos);

    (*board).setCellState(pos.y, pos.x, Player1);
    return pos.toString();
}

std::string TaskManager::boardUp(std::vector<std::string> const &args) {
    (*board).reset();
    isBoardInConfiguration = true;
    return MSG_NO_RESPONSE;
}

std::string TaskManager::configure(std::vector<std::string> const &args) {
    if (args.size() == 3)
    {
        auto x = static_cast<uint32_t>(std::stoi(args[0]));
        auto y = static_cast<uint32_t>(std::stoi(args[1]));
        auto p = static_cast<uint32_t>(std::stoi(args[2]));

        if (isInBound(x) && isInBound(y) && p == 1 || p == 2) {
            (*board).setCellState(x, y, static_cast<CellState>(p));
        }
    }
    return MSG_NO_RESPONSE;
}

std::string TaskManager::done(std::vector<std::string> const &args) {
    Position pos;

    // TODO Calculate our move
    getIaPlay(pos);
    isBoardInConfiguration = false;
    return pos.toString();
}

std::string TaskManager::unknown(std::vector<std::string> const &args) {
    return MSG_UNKNOWN;
}

std::string TaskManager::about(std::vector<std::string> const &args) {
    return MSG_ABOUT;
}

std::string TaskManager::restart(std::vector<std::string> const &args) {
    (*board).reset();
    return MSG_OK;
}

std::string TaskManager::end(std::vector<std::string> const &args) {
    coreRunning = false;
    return MSG_NO_RESPONSE;
}

std::string TaskManager::takeBack(std::vector<std::string> const &args) {
    if (args.size() != 2)
        return MSG_ERROR + " expecting TURN with format TAKEBACK [x],[y]";
    auto x = static_cast<uint32_t >(std::stoi(args[0]));
    auto y = static_cast<uint32_t >(std::stoi(args[1]));

    if ((x < 0 || x > size) || (y < 0 || y > size))
        return MSG_ERROR + " expecting x and y in range 0..18";
    (*board).setCellState(y, x, Empty);
    return "OK";
}

std::string TaskManager::rectstart(std::vector<std::string> const &args) {
    return MSG_ERROR + " rectangular board are not supported";
}

bool TaskManager::isInBound(int x) const {
    return (x < 19 && x >= 0);
}

TaskManager::TaskManager(bool &running, uint32_t boardSize):
        tasks({
                      {"START", &TaskManager::start},
                      {"BEGIN", &TaskManager::begin},
                      {"INFO", &TaskManager::nomessage},
                      {"BOARD", &TaskManager::boardUp},
                      {"DONE", &TaskManager::done},
                      {"TURN", &TaskManager::turn},
                      {"END", &TaskManager::end},
                      {"ABOUT", &TaskManager::unknown},
                      {"RECTSTART", &TaskManager::rectstart},
                      {"RESTART", &TaskManager::restart},
                      {"TAKEBACK", &TaskManager::takeBack},
                      {"PLAY", &TaskManager::unknown},
                      {"ABOUT", &TaskManager::about},
                      {"CONFIGURE", &TaskManager::configure}
              }),
        splitter(),
        size(boardSize),
        coreRunning(running),
        board(std::make_unique<Board>())
{
}

std::string TaskManager::nomessage(std::vector<std::string> const &args) {
    return MSG_NO_RESPONSE;
}

bool TaskManager::canIWin(Board &myBoard, Position &out, CellState player)
{
    //TODO Check if the player can win this round
    return false;
}

bool TaskManager::enemyCanWin(Board &myBoard, Position &out, CellState player)
{
    //TODO Check if the enemy can win next round
    return false;
}

CellState TaskManager::recurs(Board &myBoard, uint32_t x, uint32_t y, CellState state) {
    CellState comp;

    //Set the piece at the position giving in param.
    myBoard.setCellState(x, y, state);

    //Check
    comp = myBoard.getChecker().hasAWinner(myBoard.getBoard());
    if (comp == Player1)
        return Player1;
    else if (comp == Player2)
        return Player2;

    Position out;
    //Change player Role;
    if (state == Player1)
        state = Player2;
    else
        state = Player1;

    // Determine if we can end the game with one move
    if (canIWin(myBoard, out, state))
    {
        if ((comp = recurs(myBoard, out.x, out.y, state)) == Player1 || comp == Player2)
            return comp;
    }
    if (enemyCanWin(myBoard, out, (state == Player2) ? Player1 : Player2))
    {
        if ((comp = recurs(myBoard, out.x, out.y, state)) == Player1 || comp == Player2)
            return comp;
    }
    // Select a random cell to perform the recursive
    do {
         out.x = static_cast<uint32_t>(std::rand() % 19);
         out.y = static_cast<uint32_t>(std::rand() % 19);
    } while (myBoard[out.y][out.x] != CellState::Empty);
    if ((comp = recurs(myBoard, out.x, out.y, state)) == Player1 || comp == Player2)
        return comp;
    return Empty;
}

uint32_t TaskManager::monteCarlo(Board &myBoard, uint32_t x, uint32_t y)
{
    uint32_t result = 0;
    auto tmpBoard = myBoard;

    //Launch x recursive here 1000, and growth the var result for each win of player 1
    for (uint32_t idx = 0; idx < 1000; ++idx)
    {
        if (recurs(tmpBoard, x, y, Player1) == Player1)
            result++;
    }
    return result;
}

void TaskManager::getIaPlay(Position &outPos) {
    Position curMax;
    // Count is the max probality value of the cell
    uint32_t count = 0;

    // Tmp will receive the return of monteCarlo algo and will be compared with count
    uint32_t tmp = 0;

    // lookinf for an Empty cell which i'll launch the monteCarlo recursive
    for (uint32_t y = 0; y < (*board).getBoard().size(); ++y)
    {
        for (uint32_t x = 0; x < (*board).getBoard()[y].size(); ++x)
        {
            if ((*board).getBoard()[y][x] == Empty) {
                if ((tmp = monteCarlo(*board, x, y)) > count) {
                    // A new max prob has been happened, so set the new pos and the new count
                    count = tmp;
                    curMax.x = x;
                    curMax.y = y;
                }
            }
        }
    }
    outPos = curMax;
}

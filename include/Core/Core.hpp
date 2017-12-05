//
// Created by 53818 on 27/11/2017.
//

#ifndef GOMOKU_CORE_H
#define GOMOKU_CORE_H

#include <string>

namespace ai {
    /**
     * Class responsable for getting messages from Piskvork, processing them to the taskmanager
     * and send its answer back to Piskvork
     */
    class Core {
    public:
        Core() = default;
        ~Core() = default;
        void run();

    private:
        /**
         * Set this variable to stop the core
         */
        bool running = true;

        std::string readString() const;
        void send(std::string const &message) const;

        // Deleted Constructors and operators
    public:
        Core(Core const &) = delete;
        Core(Core &&) = delete;
        Core &operator=(Core const &) = delete;
        Core &operator=(Core &&) = delete;
    };
}
#endif //GOMOKU_CORE_H
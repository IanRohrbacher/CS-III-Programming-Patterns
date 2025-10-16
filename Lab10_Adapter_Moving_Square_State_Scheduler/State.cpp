#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <string>

using String = std::string;

// Forward declaration of Process
class Process;

// Base State class
class State {
    public:
        virtual void dispatch(Process*) {};
        virtual void suspend(Process*) {};
        virtual void block(Process*) {};
        virtual void exit(Process*) {};
        virtual String report() = 0;
        virtual ~State() {};
};

// ReadyState class
class ReadyState : public State {
    public:
        static State* instance() {
            static ReadyState instance;
            return &instance;
        };
        void dispatch(Process* process) override;
        String report() override { return "ready"; };
};

// RunningState class
class RunningState : public State {
    public:
        static State* instance() {
            static RunningState instance;
            return &instance;
        };
        void suspend(Process* process) override;
        void block(Process* process) override;
        void exit(Process* process) override;
        String report() override { return "running"; };
};

// BlockedState class
class BlockedState : public State {
    public:
        static State* instance() {
            static BlockedState instance;
            return &instance;
        };
        void dispatch(Process* process) override;
        String report() override { return "blocked"; };
};

// ExitState class
class ExitState : public State {
    public:
        static State* instance() {
            static ExitState instance;
            return &instance;
        };
        String report() override { return "exiting"; };
};

// Process class definition
class Process {
    public:
        Process() {
            static int idCounter = 1;
            id = idCounter++;
            state = ReadyState::instance();
        };
        void changeState(State* newState) {
            state = newState;
            std::cout << "Process " << id << " is " << state->report() << std::endl;
        };
        void dispatch() { state->dispatch(this); };
        void suspend() { state->suspend(this); };
        void block() { state->block(this); };
        void exit() { state->exit(this); };

    private:
        int id;
        State* state;
};

// Implementations of State methods
void ReadyState::dispatch(Process* process) {
    process->changeState(RunningState::instance());
}

void RunningState::suspend(Process* process) {
    process->changeState(ReadyState::instance());
}

void RunningState::block(Process* process) {
    process->changeState(BlockedState::instance());
}

void RunningState::exit(Process* process) {
    process->changeState(ExitState::instance());
}

void BlockedState::dispatch(Process* process) {
    process->changeState(ReadyState::instance());
}

// Scheduler class
class Scheduler {
    public:
        static Scheduler& getInstance() {
            static Scheduler instance;
            return instance;
        };
        Scheduler(const Scheduler&) = delete;
        Scheduler& operator=(const Scheduler&) = delete;

        void schedule(int processCount) {
            for (int i = 0; i < processCount; i++) {
                readyQueue.push(new Process());
                std::cout << "Creating Process " << (i + 1) << "...\n";
            };
        };
        bool isClear() { return readyQueue.empty() && blockedQueue.empty(); };
        void run() {
            if ((rand() % 100) > (rand() % 100) && !blockedQueue.empty()) {
                std::cout << "Unblocking...\n";
                Process* top = blockedQueue.front();
                blockedQueue.pop();
                top->dispatch();
                readyQueue.push(top);
                std::cout << std::endl;
            }

            if (!readyQueue.empty()) {
                Process* active = readyQueue.front();
                readyQueue.pop();
                active->dispatch();

                switch (rand() % 3) {
                    case 0:
                        std::cout << "Exiting...\n";
                        active->exit();
                        delete active;
                        break;

                    case 1:
                        std::cout << "Suspending...\n";
                        active->suspend();
                        readyQueue.push(active);
                        break;

                    case 2:
                        std::cout << "Blocking...\n";
                        active->block();
                        blockedQueue.push(active);
                        break;
                }
                std::cout << std::endl;
            }
        };

    private:
        Scheduler() {
            readyQueue = std::queue<Process*>();
            blockedQueue = std::queue<Process*>();
        };
        ~Scheduler() {
            while (!readyQueue.empty()) {
                delete readyQueue.front();
                readyQueue.pop();
            }
            while (!blockedQueue.empty()) {
                delete blockedQueue.front();
                blockedQueue.pop();
            }
        };

        std::queue<Process*> readyQueue;
        std::queue<Process*> blockedQueue;
};

int main() {
    std::srand(std::time(nullptr));

    Scheduler& scheduler = Scheduler::getInstance();
    scheduler.schedule(4);

    std::cout << "\n---------- scheduler running -------------\n\n";
    while (!scheduler.isClear()) {
        scheduler.run();
    }
    std::cout << "---------- scheduler done -------------\n";

    return 0;
}

// implements command history (multiple undos)
// demonstrates command pattern
// Mikhail Nesterenko
// 11/7/2024

#include <iostream>
#include <vector>
#include <string>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

// receiver
class Document {
public:
    Document(const vector<string> &lines = {}) : lines_(lines) {}

    // actions
    void insert(int line, const string &str) {
        const int index = line - 1;
        if (index <= lines_.size())
            lines_.insert(lines_.begin() + index, str);
        else
            cout << "line out of range" << endl;
    }

    const string remove(int line) {
        const int index = line - 1;
        string deletedLine = "";
        if (index < lines_.size()) {
            deletedLine = *(lines_.begin() + index);
            lines_.erase(lines_.begin() + index);
        }
        else
            cout << "line out of range" << endl;
        return deletedLine;
    }

    void show() const {
        for (int i = 0; i < lines_.size(); ++i)
            cout << i + 1 << ". " << *(lines_.begin() + i) << endl;
    }

private:
    vector<string> lines_;
};

// abstract command
class Command {
public:
    Command(Document *doc) : doc_(doc) {}
    virtual void execute() = 0;
    virtual void unexecute() = 0;
    virtual string show() = 0;
    virtual Command* clone() const = 0;
    virtual ~Command() {}

protected:
    Document *doc_;
};

// InsertCommand
class InsertCommand : public Command {
public:
    InsertCommand(Document *doc, int line, const string &str) : Command(doc), line_(line), str_(str) {}
    void execute() override { doc_->insert(line_, str_); }
    void unexecute() override { doc_->remove(line_); }
    string show() override { return "insert \"" + str_ + "\" at line " + std::to_string(line_); }
    Command* clone() const override { return new InsertCommand(*this); }

private:
    int line_;
    string str_;
};

// EraseCommand
class EraseCommand : public Command {
public:
    EraseCommand(Document *doc, int line) : Command(doc), line_(line), str_("") {}
    void execute() override { str_ = doc_->remove(line_); }
    void unexecute() override { doc_->insert(line_, str_); }
    string show() override { return "erase line " + std::to_string(line_); }
    Command* clone() const override { return new EraseCommand(*this); }

private:
    int line_;
    string str_;
};

// invoker
class DocumentWithHistory {
public:
    DocumentWithHistory(const vector<string> &doc = {}) : doc_(doc), storedDoc_(nullptr) {}

    void insert(int line, const string &str) {
        Command *com = new InsertCommand(&doc_, line, str);
        com->execute();
        doneCommands_.push(com);
    }

    void erase(int line) {
        Command *com = new EraseCommand(&doc_, line);
        com->execute();
        doneCommands_.push(com);
    }

    void undo() {
        if (!doneCommands_.empty()) {
            Command *com = doneCommands_.top();
            doneCommands_.pop();
            com->unexecute();
            delete com;
        } else {
            cout << "no commands to undo" << endl;
        }
    }

    void print() const { doc_.show(); }

    void show() const {
        std::stack<Command *> temp = doneCommands_;
        int i = 1;
        while (!temp.empty()) {
            cout << i << ". " + (temp.top())->show() << endl;
            temp.pop();
            i++;
        }
    }

    void checkpoint();
    bool rollback();

    void copyCommand(int num) {
        if (doneCommands_.empty()) {
            cout << "no commands to redo" << endl;
            return;
        }

        std::stack<Command *> temp = doneCommands_;
        int i = 1;
        while (!temp.empty()) {
            if (i == num) {
                Command *copiedCommand = temp.top()->clone();
                copiedCommand->execute();
                doneCommands_.push(copiedCommand);
                return;
            }
            temp.pop();
            i++;
        }
        cout << "number out of bounds" << endl;
    }

private:
    Document doc_;
    std::stack<Command*> doneCommands_;

    class Memento* storedDoc_;
    std::stack<Command*> storedCommands_;
};

// Memento class definition
class Memento {
public:
    Memento(const DocumentWithHistory* doc) : doc_(new DocumentWithHistory(*doc)) {}
    ~Memento() { delete doc_; }
    const DocumentWithHistory *getState() const { return doc_; }

private:
    const DocumentWithHistory* doc_;
};

void DocumentWithHistory::checkpoint() {
    if (storedDoc_) {
        delete storedDoc_;
    }
    while (!storedCommands_.empty()) {
        delete storedCommands_.top();
        storedCommands_.pop();
    }
    std::stack<Command*> temp = doneCommands_;
    while (!temp.empty()) {
        storedCommands_.push(temp.top()->clone());
        temp.pop();
    }
    storedDoc_ = new Memento(this);
}

bool DocumentWithHistory::rollback() {
    if (storedDoc_) {
        doc_ = storedDoc_->getState()->doc_;

        while (!doneCommands_.empty()) {
            delete doneCommands_.top();
            doneCommands_.pop();
        }

        std::stack<Command*> temp = storedCommands_;
        while (!temp.empty()) {
            doneCommands_.push(temp.top()->clone());
            temp.pop();
        }

        delete storedDoc_;
        storedDoc_ = nullptr;
        return true;
    }
    return false;
}

// client
int main() {
    DocumentWithHistory his({"Lorem Ipsum is simply dummy text of the printing and typesetting",
                             "industry. Lorem Ipsum has been the industry's standard dummy text",
                             "ever since the 1500s, when an unknown printer took a galley of",
                             "type and scrambled it to make a type specimen book. It has",
                             "survived five centuries."});

    char option;
    do {
        his.print();
        cout << endl;

        cout << "Enter option (i)nsert line | (e)rase line | (u)ndo last command | (c)heckpoint | roll(b)ack | (h)istory | (r)edo command: (d)one to exit: ";
        cin >> option;

        int line;
        string str;
        switch (option) {
            case 'i':
                cout << "line number to insert: ";
                cin >> line;
                cout << "line to insert: ";
                cin.get();
                getline(cin, str);
                his.insert(line, str);
                break;

            case 'e':
                cout << "line number to remove: ";
                cin >> line;
                his.erase(line);
                break;

            case 'u':
                his.undo();
                break;

            case 'c':
                cout << "Checkpoint Made!\n";
                his.checkpoint();
                break;

            case 'b':
                if (his.rollback()) {
                    cout << "Checkpoint Loaded!\n";
                } else {
                    cout << "No Checkpoint Found!\n";
                }
                break;

            case 'h':
                his.show();
                break;

            case 'r':
                cout << "enter a command number: ";
                cin >> line;
                his.copyCommand(line);
                break;

            case 'd':
                break;
            default:
                cout << "Invalid Key!\n";
                break;
        }
        cout << "----------------------------------------\n";

    } while (option == 'i' || option == 'e' || option == 'u' || option == 'c' || option == 'b' || option == 'h' || option == 'r' || option != 'd');
}

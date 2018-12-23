#include "WhileCommand.h"


int WhileCommand::execute() {
    // beck up for the while loop queue.
    queue<string> whileScope = whileOrders;
    int x = 0;
    Command *c;
    // if the condition is false.
    if (!ControlParser::execute()) {
        // taking out all of the orders from the queue.
        while (whileOrders.front() != "}") {
            whileOrders.pop();
        }
        whileOrders.pop();
    }
    // when the condition is true.
    while (ControlParser::execute()) {
        whileOrders = whileScope;
        // this is the offset.
        x += 1;
        string token = whileOrders.front();
        /* not popping immidiatlly cuz
         * of the assign command (x = 3 for example.*/
        if (!symbolTable.isVarExist(token)) {
            whileOrders.pop();
        }
        while (token != "}") {
            if (token == "{") {
                token = whileOrders.front();
                // for the assign command.
                if (!symbolTable.isVarExist(token)) {
                    whileOrders.pop();
                }
                continue;
            }
            c = getCommand(token);
            if (c != nullptr) {
                c->execute();
                delete c;
            } else {
                throw CommandException("while loop!");
            }
            token = whileOrders.front();
            if (!symbolTable.isVarExist(token)) {
                whileOrders.pop();
            }
        }
    }
    return x;
}

queue<string> WhileCommand::getOrdersAsQueue() {
    // getting the orders for the while loop as list.
    queue<string> ordersQueue;
    string token = orders.front();
    orders.pop();
    int counter = 0;
    do {
        if (token == "{") {
            counter++;
        } else if (token == "}") {
            counter--;
        }
        ordersQueue.push(token);
        if (!orders.empty() && counter != 0) {
            token = orders.front();
            orders.pop();
        }
    } while (counter != 0);
    return ordersQueue;
}

Command *WhileCommand::getCommand(const string &name) {
    // returning the right command to be executed.
    if (name == "print") {
        return new PrintCommand(symbolTable, whileOrders);
    } else if (name == "sleep") {
        return new SleepCommand(whileOrders);
        //} else if (name == "if") {
        //    return new IfCommand(symbolTable, whileOrders);

    } else if (symbolTable.isVarExist(name)) {
        return new AssignCommand(whileOrders, symbolTable);
    } else if (name == "while") {
        return new WhileCommand(symbolTable, whileOrders);
    } else if (name == "var") {
        return new DefineVarCommand(whileOrders, symbolTable);
    } else {
        return nullptr;
    }
}
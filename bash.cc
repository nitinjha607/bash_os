
 
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;
std::string current_prompt = "";
// types and definitions live in "C land" and must be flagged
extern "C" {
#include "parser.tab.h"
#include "bash.h"
extern "C" void yyset_debug(int d);
}

// global debugging flag
int debug = 0;

int main(int argc, char *argv[]) {
    if (debug)
        yydebug = 1;  /* turn on ugly YACC debugging */

    current_prompt = "";  // Initialize to empty string

    /* parse the input file */
    yyparse();

    exit(0);
}
void execute_command(struct command *cmd) {
    if (strcmp(cmd->command, "echo") == 0 || strcmp(cmd->command, "/bin/echo") == 0) {
        for (int i = 1; i < cmd->argc; i++) {
            if (i > 1) std::cout << " ";
            std::string arg = cmd->argv[i];

            if (arg.length() >= 2) {
                // Handle double and single quotes without adding extra quotes
                if ((arg.front() == '"' && arg.back() == '"') || 
                    (arg.front() == '\'' && arg.back() == '\'')) {
                    std::cout << arg.substr(1, arg.length() - 2);  // Remove outer quotes
                } else {
                    std::cout << arg;  // Print as is
                }
            } else {
                std::cout << arg;  // Handle short arguments
            }
        }
        std::cout << std::endl;
    } else if (strncmp(cmd->command, "PS1=", 4) == 0) {
        current_prompt = cmd->command + 4;  // Handle PS1 setting
    }
}


void doline(struct command *pcmd) {
    while (pcmd) {
        // Check if PS1 is set and print it before the command
        if (!current_prompt.empty()) {
            std::cout << current_prompt;
        }
        
        if (strncmp(pcmd->command, "PS1=", 4) == 0) {
            // Handle PS1 setting
            current_prompt = pcmd->command + 4;
        } else {
            execute_command(pcmd);  // Execute the command
        }
        pcmd = pcmd->next;
    }
}

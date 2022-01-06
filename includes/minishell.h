# ifndef MINISHELL_H
#define MINISHELL_H

#define READ 0
#define WRITE 1



#include "lexer.h"
#include "utils.h"
#include "errors.h"
#include "free.h"
#include "test.h"
#include "built_in.h"
#include "exec.h"
#include "ctrlsignal.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#define __USE_GNU 1
#define __USE_POSIX 1
#define __USE_POSIX199506 1
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

#endif
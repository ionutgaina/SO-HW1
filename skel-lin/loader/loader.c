/*
 * Loader Implementation
 *
 * 2022, Operating Systems
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <signal.h>

#include "exec_parser.h"

static so_exec_t *exec;

static void segv_handler(int signum, siginfo_t *info, void *context)
{
	

	printf("address fault - %p\n", info->si_addr);
	printf("signum - %d\n", signum);
	printf("context - %p\n", context);

	printf("\nexec struct\n\n");

	printf("base_addr: %p\n", exec->base_addr);
	printf("entry - %p\n", exec->entry);
	printf("segments_no - %d\n", exec->segments_no);

	/* TODO - actual loader implementation */
	exit(0);
}

int so_init_loader(void)
{
	int rc;
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = segv_handler;
	sa.sa_flags = SA_SIGINFO;
	rc = sigaction(SIGSEGV, &sa, NULL);
	if (rc < 0) {
		perror("sigaction");
		return -1;
	}
	return 0;
}

int so_execute(char *path, char *argv[])
{
	exec = so_parse_exec(path);
	if (!exec)
		return -1;

	so_start_exec(exec, argv);

	return -1;
}
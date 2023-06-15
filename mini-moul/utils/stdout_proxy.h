#ifndef STDOUT_PROXY_H
# define STDOUT_PROXY_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <unistd.h>

/**
 * Start redirecting standard output to file.
 * Must end with `stdout_close()`.
 * @return Standard output file number (use in `stdout_close()`)
*/
int	stdout_open(void)
{
	int	saved_stdout;
	int	output_fileno;

	fflush(stdout);
	saved_stdout = dup(STDOUT_FILENO);
	output_fileno = open(".stdout", O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	dup2(output_fileno, STDOUT_FILENO);
	close(output_fileno);
	return (saved_stdout);
}

/**
 * Stop redirecting standard output and read file content.
 * @param saved_stdout Standard output file number
 * (returned from `stdout_open()`)
 * @param buffer buffer to retrieve redirected contents.
 * @param size sizeof buffer
 * @return Standard output file number (use in `stdout_close()`)
*/
char	*stdout_close(int saved_stdout, char *buffer, unsigned int size)
{
	FILE	*fp;

	fflush(stdout);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	memset(buffer, 0, size);
	fp = fopen(".stdout", "r");
	fgets(buffer, size, fp);
	fclose(fp);
	remove(".stdout");
	return (buffer);
}

#endif

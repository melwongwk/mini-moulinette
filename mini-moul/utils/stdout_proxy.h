#ifndef STDOUT_PROXY_H
# define STDOUT_PROXY_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <unistd.h>

/**
 * Read contents of file to buffer
 * @return buffer (must be freed).
*/
char	*freadall(FILE *fp)
{
	int				result;
	unsigned long	flen;
	char			*buffer;

	if (fp == NULL)
		return (NULL);
	result = fseek(fp, 0, SEEK_END);
	if (result != 0)
		return (NULL);
	flen = ftell(fp);
	result = fseek(fp, 0, SEEK_SET);
	if (result != 0)
		return (NULL);
	buffer = (char *)malloc(flen + 1);
	if (buffer == NULL)
		return (NULL);
	if (fread(buffer, 1, flen, fp) != flen)
		return (NULL);
	buffer[flen] = '\0';
	return (buffer);
}

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
 * Read redirected standard output.
 * @return buffer (must be freed)
*/
char	*stdout_read(void)
{
	FILE	*fp;
	char	*buffer;

	fflush(stdout);
	fp = fopen(".stdout", "r");
	buffer = freadall(fp);
	fclose(fp);
	return (buffer);
}

/**
 * Stop redirecting standard output.
 * @param saved_stdout Standard output file number
 * (returned from `stdout_open()`)
*/
void	stdout_close(int saved_stdout)
{
	fflush(stdout);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	remove(".stdout");
	return ;
}

/**
 * Execute and extract output to buffer.
 * @param command Command
 * @return buffer (must be freed)
*/
char	*stdout_exec(char *command)
{
	FILE	*fp;
	char	*buffer;

	fp = popen(command, "r");
	buffer = freadall(fp);
	fclose(fp);
	return (buffer);
}

#endif

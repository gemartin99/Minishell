#include "../inc/minishell.h"

int ft_atoi_error(int *atoi_error)
{
	*atoi_error = -1;
	return (-1);
}

long long	static ft_special_atoi(const char *str, int *atoi_error)
{
	int				i;
	int				valorfinal;
	long long	nbr;

	nbr = 0;
	i = 0;
	valorfinal = 1;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			valorfinal = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
		if (nbr < -LLONG_MIN && valorfinal == -1)
			return (ft_atoi_error(atoi_error));
		if (nbr > LLONG_MAX && valorfinal == 1)
			return (ft_atoi_error(atoi_error));
	}
	return (nbr * valorfinal);
}

int ft_validate_num(char c)
{
	if ((c < '0' || c > '9') && c != 34 && c != 39)
		return (1);
	return (0);
}

void return_value_exit(long long n)
{
	while (n > 255)
		n = n - 256;
	while (n < -255)
		n = n + 256;
	if (n < 0)
		n = n + 256;
	exit (n);
}

int check_only_num(char *s)
{
	int i;

	i = 0;
	//printf("|%s\n", s);
	if (s[i] && (s[i] == '+' || s[i] == '-'))
		i++;
	while (s[i])
	{
		if ((s[i] < '0' || s[i] > '9'))
		{
			printf("exit\nbash: exit: %s: numeric argument required\n", s);
			exit (255);
		}
		i++;
	}
	return (0);
}

void check_only_num_in_args(t_cmd *cmd) //funcion para comprobar que todos los argumentos contengan solo digitos
{
	int i;

	i = 0;
	while (cmd->arg[i])
	{
		check_only_num(cmd->arg[i]);
		i++;
	}
}

//si pones exit &&12345 12345 hace exit sin errores
//exit 12345 12345 no hace exit
void	ft_exit(t_cmd *cmd)
{
	long long n;
	char *num_in_string;
	int atoi_error;

	//hacer funcion que quite las comillas de los args
	atoi_error = 0;
	if (cmd->num_arg == 0)
		exit (0); //exit de valor de la variable global
	else if (cmd->num_arg > 1 && check_only_num(cmd->arg[0]) == 0)
		return((void)printf("exit\nbash: exit: too many arguments\n"));
	check_only_num_in_args(cmd);
	n = ft_special_atoi(cmd->arg[0], &atoi_error);
	//printf("AE %d\n", atoi_error);
	if (n > -9223372036854775807 || n < 9223372036854775807 || atoi_error == -1)
		printf("%s\n", "CAGASTE");
	//printf("exit\nbash: exit: %s: numeric argument required\n", num_in_string);
	//hacer funcion para liberar todo
	//exit (255);
	return_value_exit(n);
}
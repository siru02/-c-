/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgu <hgu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 14:48:13 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/14 21:40:03 by hgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# define D_QUOTATION 0
# define S_QUOTATION 1
# define LITERAL 2
# define WHITE_SPACE 3
# define COMMAND 5
# define OPTION 6
# define REDIR_LEFT 7
# define REDIR_RIGHT 8
# define REDIR_TWO_LEFT 9
# define REDIR_TWO_RIGHT 10
# define PIPE 11
# define BUILTIN 12
# define FILENAME 13

# define DUP2_ERRMSG "dup2 error"
# define MALLOC_ERRMSG "malloc error"
# define OPEN_ERRMSG "open error"
# define CLOSE_ERRMSG "close error"
# define WRITE_ERRMSG "write error"

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <signal.h>
# include <termios.h>

int g_exit_status;

typedef struct s_list_hrdc
{
	int					cnt;
	struct s_list_hrdc	*next;
}				t_list_hrdc;

typedef struct s_token
{
	int				type;
	int				quote_start; //1105
	int				quote_end; //1105
	int				expansion_cnt; //1105
	int				expansion_idx;//1105 확장이 끝난 지점의 바로 다음 idx반환
	int				flag; //확장시 ""안에서 확장하는지 여부를 저장할 플래그
	char			*value;
	char			*expansion_fail;
	struct s_token	*next;
}				t_token;

typedef struct s_simple_cmd
{
	char	*cmd_path;
	char	**cmd_argv;
	int		argv_cnt;
}				t_simple_cmd;

typedef struct s_redirect
{
    int     type;
    int     token_cnt; //extention 한 결과에서 (공백 + 1) 만큼저장 //"$a"의 경우에는 사용하지 않는다 //split.c의 단어개수새는 함수에 ' '를 인자로 넣어서 카운트
    char    *filename; //입력받은 실제 파일이름
}               t_redirect;

typedef struct s_redirect_s
{
	t_redirect			*redirect;
	struct s_redirect_s	*redirect_s;
}				t_redirect_s;

typedef struct s_cmd
{
	t_redirect_s	*redirect_s;
	t_simple_cmd	*simple_cmd;
}				t_cmd;

typedef struct s_pipe
{
	t_cmd			*cmd;
	struct s_pipe	*pipe;
	int				flag;
}				t_pipe;

typedef struct s_bundle
{
	char		**envp;
	int			envp_len;
	t_list		*hrdc_filename_list;
	t_list		*current_filename;
	t_list_hrdc	*hrdc_cnt_list;
	t_list_hrdc	*current_cnt;
	int			fd[2];
	char		*err_msg;
	int			err_flag;
	int			cmd_cnt;
	int			last_pid;
	int			fork_cnt;
	t_pipe		*current;
}				t_bundle;

void		cp_envp(t_bundle *bundle, char *envp[]);
int			check_one_cmd_and_builtin(t_pipe *root);
int			is_builtin(char *cmd_name);
int			exec_recur(t_pipe *root,
				t_bundle *bundle, int before_fd_read, int cmd_idx);
int			exec_cmd(t_cmd *cmd, t_bundle *bundle,
				int before_fd_read, int cmd_idx);
void		exec_redirect_s_recur(t_redirect_s *redirect_s, t_bundle *bundle);
void		exec_redirect(t_redirect *redirect, t_bundle *bundle);
void		exec_simple_cmd(t_simple_cmd *simple_cmd, t_bundle *bundle,
				int idx);
void		redir_left(char *filename);
void		redir_right(char *filename);
void		redir_two_left(t_bundle *bundle);
void		redir_two_right(char *filename);
char		**get_path(char **envp);
void		free_2d_malloced_str(char **str_arr);
void		base_redir_first_cmd(t_bundle *bundle);
void		base_redir_mid_cmd(t_bundle *bundle, int before_fd_read);
void		base_redir_last_cmd(t_bundle *bundle, int before_fd_read);
void		init_bundle(t_bundle *bundle);
void		cp_envp(t_bundle *bundle, char *envp[]);
int			pre_exec_here_doc(t_pipe *root, t_bundle *bundle);
t_list_hrdc	*ft_lstnew_hrdc(void);
void		ft_lstadd_back_hrdc(t_list_hrdc **lst, t_list_hrdc *new);
int			search_here_doc(t_redirect_s *redirect_s,
				t_bundle *bundle, t_list_hrdc *new);
int			exec_here_doc(char *eof, t_bundle *bundle);
int			write_to_tempfile_until_eof(char *eof, int tempfile_fd);
void		ft_exit(char **cmd_argv);
int			env(t_bundle *bundle);
void		rm_inp_env_var(t_bundle *bundle, int found_idx);
size_t		ft_env_var_len(const char *s);
int			is_in_envp(t_bundle *bundle, char *inp_str);
int			unset(t_bundle *bundle, char **cmd_argv);
int			check_execption(char *inp);
void		append_new_env_var(t_bundle *bundle,
				int ret_envp_idx, char *new_str);
int			export(t_bundle *bundle, char **cmd_argv);
int			pwd(void);
char		*getenv_minishell(t_bundle *bundle, char *var_name);
int			cd(t_bundle *bundle, char **cmd_argv);
int			echo(char **cmd_argv);
int			check_exeception(char *inp);
int			print_2d_str(char **str_arr);
int			exec_builtin(char *cmd_name, char **cmd_argv, t_bundle *bundle);
int			ft_atoi_exit(const char *str);
void		sigint_handler(int sig);
void		sigint_handler_during_fork(int sig);
void		sigquit_handler(int sig);
void		sigquit_handler_during_fork(int sig);
void		free_tree(t_pipe *root);
void		free_cmd(t_cmd *cmd);
void		free_redirect_s(t_redirect_s *redirect_s);
void		free_redirect(t_redirect *redirect);
t_list_hrdc	*ft_lstnew_hrdc(void);
void		ft_lstadd_back_hrdc(t_list_hrdc **lst, t_list_hrdc *new);
void		free_token(t_token *token);
int			free_bundle(t_bundle *bundle);
int			check_file_exist(t_redirect_s *redirect_s);
void		free_hrdc_nodes(t_bundle *bundle);
void		select_err_msg(char *cmd_path);
void		print_cmd_not_found_err(t_simple_cmd *simple_cmd);
void		free_hrdc_nodes(t_bundle *bundle);
void		ctrl_d_handler(void);
void		exec_command(t_bundle *bundle, t_pipe *root);
int			exec_tree(t_bundle *bundle, t_pipe *root);
void		get_fork_cnt(t_bundle *bundle, t_pipe *root);
void		setting(int argc, char *argv[], t_bundle *bundle, char *envp[]);
void		set_exit_status(t_bundle *bundle);
int			exec_one_builtin(t_bundle *bundle, t_pipe *root);
void		sigint_handler_during_heredoc(int sig);
void		sigquit_handler_during_heredoc(int sig);
void		restore_setting_after_here_doc(int before_stdin);
int			check_exit_status(void);
void		write_a_line_to_tempfile(char **inp, int tempfile_fd, int inp_len);
int			write_to_tempfile_until_eof(char *eof, int tempfile_fd);
char		*get_var_name(char *str);
int			exist_already(t_bundle *bundle, char *new_str);
void		append_new_env_var(t_bundle *bundle,
				int ret_envp_idx, char *new_str);
int			print_declare_env(char **str_arr);
int			err_in_echo(void);
int			err_in_cd(char *dest);
void		err_in_export(char *str);



t_token	*syntax_analyze(t_token *token_head);
t_pipe	*make_tree(t_token *token_head, t_bundle *bundle);
t_token	*free_all_token(t_token *token_head);
t_token	*tokenize(char *str);
int	jump_quote(char *s, int idx);
int	check_ch_is_token(char *str);
void	make_token(char *str, int len, int type, t_token **head);
t_token	*free_all_token(t_token *token_head);
void	make_redirect_s(t_redirect_s **head, t_token *token, t_pipe *pipe, t_bundle *bundle);
t_redirect	*make_redirect(t_token *token, t_pipe *pipe);
t_pipe	*make_pipe(void);
t_cmd	*make_cmd(void);
void	make_simple_cmd(t_cmd *cmd, t_token *token, t_bundle *bundle);
void	copy_strings(char **new, char **old, int cnt);
void	print_tree(t_pipe *node, t_bundle *bundle);
void	error_pipe(t_pipe *pipe, t_bundle *bundle);
void	delete_quote_after_expansion(t_token *token); //1105
char	*new_cut_quote(int open, int close, char *target);//1105
t_token	*expansion_main(t_token *head, t_bundle *bundle);//1105
void	delete_quote(t_token *tk);//1105
void	find_close_quote_with_dollar(t_token *token, int *close_quote);
void	del_quote_before_close_quote(t_token *token, int *close_quote, int idx, char ch);
#endif
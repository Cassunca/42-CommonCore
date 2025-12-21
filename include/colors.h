/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 10:44:28 by kamys             #+#    #+#             */
/*   Updated: 2026/01/22 11:26:22 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

/* ===================== */
/* RESET / NORMAL        */
/* ===================== */

# define RESET        "\033[0m"

/* ===================== */
/* TEXT STYLES           */
/* ===================== */

# define BOLD         "\033[1m"
# define DIM          "\033[2m"
# define ITALIC       "\033[3m"
# define UNDERLINE    "\033[4m"
# define BLINK        "\033[5m"
# define REVERSE      "\033[7m"
# define HIDDEN       "\033[8m"

/* ===================== */
/* FOREGROUND COLORS     */
/* ===================== */

# define BLACK        "\033[30m"
# define RED          "\033[31m"
# define GREEN        "\033[32m"
# define YELLOW       "\033[33m"
# define BLUE         "\033[34m"
# define MAGENTA      "\033[35m"
# define CYAN         "\033[36m"
# define WHITE        "\033[37m"

/* ===================== */
/* BRIGHT FOREGROUND     */
/* ===================== */

# define B_BLACK      "\033[90m"
# define B_RED        "\033[91m"
# define B_GREEN      "\033[92m"
# define B_YELLOW     "\033[93m"
# define B_BLUE       "\033[94m"
# define B_MAGENTA    "\033[95m"
# define B_CYAN       "\033[96m"
# define B_WHITE      "\033[97m"

/* ===================== */
/* BACKGROUND COLORS     */
/* ===================== */

# define BG_BLACK     "\033[40m"
# define BG_RED       "\033[41m"
# define BG_GREEN     "\033[42m"
# define BG_YELLOW    "\033[43m"
# define BG_BLUE      "\033[44m"
# define BG_MAGENTA   "\033[45m"
# define BG_CYAN      "\033[46m"
# define BG_WHITE     "\033[47m"

/* ===================== */
/* BRIGHT BACKGROUND     */
/* ===================== */

# define BG_B_BLACK   "\033[100m"
# define BG_B_RED     "\033[101m"
# define BG_B_GREEN   "\033[102m"
# define BG_B_YELLOW  "\033[103m"
# define BG_B_BLUE    "\033[104m"
# define BG_B_MAGENTA "\033[105m"
# define BG_B_CYAN    "\033[106m"
# define BG_B_WHITE   "\033[107m"

#endif
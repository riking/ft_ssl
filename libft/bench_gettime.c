/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench_gettime.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyork <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 10:23:14 by kyork             #+#    #+#             */
/*   Updated: 2017/05/15 10:37:31 by kyork            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BENCH_GETTIME_C
# define BENCH_GETTIME_C

# ifdef BENCH_TIME_STATIC
#  define BENCH_TIME_DECL(r) static r
# else
#  define BENCH_TIME_DECL(r) r
# endif

# define BILLION 1000000000L
# define MILLION 1000000L

/*
** This file meant to be #include'd in another .c file, hence all static
*/

# include <time.h>
# include <stdlib.h>
# if defined(__MACH__)
#  include <mach/mach_time.h>

BENCH_TIME_DECL(uint64_t)					g_time_start;
BENCH_TIME_DECL(mach_timebase_info_data_t)	g_timebase = {0, 0};

BENCH_TIME_DECL(void)						bench_gettime_init(void)
{
	if (mach_timebase_info(&g_timebase) != 0)
		abort();
	g_time_start = mach_absolute_time();
}

BENCH_TIME_DECL(uint64_t)					bench_gettime(void)
{
	uint64_t	clock;
	uint64_t	nano;

	if (g_time_start == 0)
	{
		bench_gettime_init();
	}
	clock = mach_absolute_time() - g_time_start;
	nano = clock * (uint64_t)g_timebase.numer / (uint64_t)g_timebase.denom;
	return (nano);
}

# elif defined(_POSIX_MONOTONIC_CLOCK)

BENCH_TIME_DECL(uint64_t)					bench_gettime(void)
{
	struct timespec	t;

	clock_gettime(CLOCK_MONOTONIC, &t);
	return (t.tv_sec * BILLION + t.tv_nsec);
}

# else
#  error Could not find a suitable nanosecond monotonic clock
# endif

# undef BENCH_TIME_DECL

#endif

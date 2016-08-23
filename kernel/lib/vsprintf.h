/*
 * src/kernel/lib/vsprintf.h
 * - 字符串格式化输出
 */
#pragma once


//typedef	char	*va_list;


size_t	vsprintf(
		char		*buf,
		const char	*fmt,
		va_list		args);
size_t	sprintf(
		char		*buf,
		const char	*fmt,
		...);

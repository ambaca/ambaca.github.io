
/**
 * Returns text in a string up until a certain character sequence is reached.
 *
 * @param source        Source input string.
 * @param split         A string which specifies a search point to break at.
 * @param part          Buffer to store string part.
 * @param partLen       Maximum length of the string part buffer.
 * @return              -1 if no match was found; otherwise, an index into source
 *                      marking the first index after the searched text.  The
 *                      index is always relative to the start of the input string.
 */
native int SplitString(const char[] source, const char[] split, char[] part, int partLen);

/**
 * Given a string, replaces all occurrences of a search string with a 
 * replacement string.
 *
 * @param text          String to perform search and replacements on.
 * @param maxlength     Maximum length of the string buffer.
 * @param search        String to search for.
 * @param replace       String to replace the search string with.
 * @param caseSensitive If true (default), search is case sensitive.
 * @return              Number of replacements that were performed.
 * @error               'search' parameter is empty.
 */
native int ReplaceString(char[] text, int maxlength, const char[] search, const char[] replace, bool caseSensitive=true);

/**
 * Given a string, replaces the first occurrence of a search string with a 
 * replacement string.
 *
 * @param text          String to perform search and replacements on.
 * @param maxlength     Maximum length of the string buffer.
 * @param search        String to search for.
 * @param replace       String to replace the search string with.
 * @param searchLen     If higher than -1, its value will be used instead of
 *                      a strlen() call on the search parameter.
 * @param replaceLen    If higher than -1, its value will be used instead of
 *                      a strlen() call on the replace parameter.
 * @param caseSensitive If true (default), search is case sensitive.
 * @return              Index into the buffer (relative to the start) from where
 *                      the last replacement ended, or -1 if no replacements were
 *                      made.
 * @error               'search' parameter is empty.
 */
native int ReplaceStringEx(char[] text, int maxlength, const char[] search, const char[] replace, int searchLen=-1, int replaceLen=-1, bool caseSensitive=true);

/** 
 * Returns the number of bytes a character is using.  This is
 * for multi-byte characters (UTF-8).  For normal ASCII characters,
 * this will return 1.
 *
 * @param source        Source input string.
 * @return              Number of bytes the current character uses.
 */
native int GetCharBytes(const char[] source);

/**
 * Returns whether a character is an ASCII alphabet character.
 *
 * @note Multi-byte characters will always return false.
 *
 * @param chr           Character to test.
 * @return              True if character is alphabetical, otherwise false.
 */
native bool IsCharAlpha(int chr);

/**
 * Returns whether a character is numeric.
 *
 * @note Multi-byte characters will always return false.
 *
 * @param chr           Character to test.
 * @return              True if character is numeric, otherwise false.
 */
native bool IsCharNumeric(int chr);

/**
 * Returns whether a character is whitespace.
 *
 * @note Multi-byte characters will always return false.
 *
 * @param chr           Character to test.
 * @return              True if character is whitespace, otherwise false.
 */
native bool IsCharSpace(int chr);

/**
 * Returns if a character is multi-byte or not.
 *
 * @param chr           Character to test.
 * @return              0 for a normal 7-bit ASCII character,
 *                      otherwise number of bytes in multi-byte character.
 */
native int IsCharMB(int chr);

/**
 * Returns whether an alphabetic character is uppercase.
 *
 * @note Multi-byte characters will always return false.
 *
 * @param chr           Character to test.
 * @return              True if character is uppercase, otherwise false.
 */
native bool IsCharUpper(int chr);

/**
 * Returns whether an alphabetic character is lowercase.
 *
 * @note Multi-byte characters will always return false.
 *
 * @param chr           Character to test.
 * @return              True if character is lowercase, otherwise false.
 */
native bool IsCharLower(int chr);

/**
 * Strips a quote pair off a string if it exists.  That is, the following 
 * replace rule is applied once:  ^"(.*)"$ -> ^\1$
 *
 * Note that the leading and trailing quotes will only be removed if both 
 * exist.  Otherwise, the string is left unmodified.  This function should 
 * be considered O(k) (all characters get shifted down).
 *
 * @param text          String to modify (in place).
 * @return              True if string was modified, false if there was no 
 *                      set of quotes.
 */
native bool StripQuotes(char[] text);

/**
 * Converts a lowercase character to its uppercase counterpart.
 *
 * @param chr           Character to convert.
 * @return              Uppercase character on success, 
 *                      no change on failure.
 */
stock int CharToUpper(int chr)
{
	if (IsCharLower(chr))
	{
		return (chr & ~(1<<5));
	}

	return chr;
}

/**
 * Converts an uppercase character to its lowercase counterpart.
 *
 * @param chr           Character to convert.
 * @return              Lowercase character on success, 
 *                      no change on failure.
 */
stock int CharToLower(int chr)
{
	if (IsCharUpper(chr))
	{
		return (chr | (1<<5));
	}
	
	return chr;
}

/**
 * Finds the first occurrence of a character in a string.
 *
 * @param str           String.
 * @param c             Character to search for.
 * @param reverse       False (default) to search forward, true to search 
 *                      backward.
 * @return              The index of the first occurrence of the character 
 *                      in the string, or -1 if the character was not found.
 */
stock int FindCharInString(const char[] str, char c, bool reverse = false)
{
	int len = strlen(str);
	
	if (!reverse)
	{
		for (int i = 0; i < len; i++)
		{
			if (str[i] == c)
			{
				return i;
			}
		}
	}
	else
	{
		for (int i = len - 1; i >= 0; i--)
		{
			if (str[i] == c)
			{
				return i;
			}
		}
	}

	return -1;
}

/**
 * Concatenates one string onto another.
 *
 * @param buffer        String to append to.
 * @param maxlength     Maximum length of entire buffer.
 * @param source        Source string to concatenate.
 * @return              Number of bytes written.
 */
stock int StrCat(char[] buffer, int maxlength, const char[] source)
{
	int len = strlen(buffer);
	if (len >= maxlength)
	{
		return 0;
	}
	
	return Format(buffer[len], maxlength-len, "%s", source);
}

/**
 * Breaks a string into pieces and stores each piece into an array of buffers.
 *
 * @param text              The string to split.
 * @param split             The string to use as a split delimiter.
 * @param buffers           An array of string buffers (2D array).
 * @param maxStrings        Number of string buffers (first dimension size).
 * @param maxStringLength   Maximum length of each string buffer.
 * @param copyRemainder     False (default) discard excess pieces, true to ignore
 *                          delimiters after last piece.
 * @return                  Number of strings retrieved.
 */
stock int ExplodeString(const char[] text, const char[] split, char[][] buffers, int maxStrings,
                    int maxStringLength, bool copyRemainder = false)
{
	int reloc_idx, idx, total;

	if (maxStrings < 1 || !split[0])
	{
		return 0;
	}

	while ((idx = SplitString(text[reloc_idx], split, buffers[total], maxStringLength)) != -1)
	{
		reloc_idx += idx;
		if (++total == maxStrings)
		{
			if (copyRemainder)
			{
				strcopy(buffers[total-1], maxStringLength, text[reloc_idx-idx]);
			}
			return total;
		}
	}

	strcopy(buffers[total++], maxStringLength, text[reloc_idx]);

	return total;
}

/**
 * Joins an array of strings into one string, with a "join" string inserted in
 * between each given string.  This function complements ExplodeString.
 *
 * @param strings       An array of strings.
 * @param numStrings    Number of strings in the array.
 * @param join          The join string to insert between each string.
 * @param buffer        Output buffer to write the joined string to.
 * @param maxLength     Maximum length of the output buffer.
 * @return              Number of bytes written to the output buffer.
 */
stock int ImplodeStrings(const char[][] strings, int numStrings, const char[] join, char[] buffer, int maxLength)
{
	int total, length, part_length;
	int join_length = strlen(join);
	for (int i=0; i<numStrings; i++)
	{
		length = strcopy(buffer[total], maxLength-total, strings[i]);
		total += length;
		if (length < part_length)
		{
			break;
		}
		if (i != numStrings - 1)
		{
			length = strcopy(buffer[total], maxLength-total, join);
			total += length;
			if (length < join_length)
			{
				break;
			}
		}
	}
	return total;
}

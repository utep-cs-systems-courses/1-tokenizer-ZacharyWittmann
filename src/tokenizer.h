#include <stdlib.h>
#ifndef _TOKENIZER_
#define _TOKENIZER_


/* Return true (non-zero) if c is a whitespace characer
   ('\t' or ' ').  
   Zero terminators are not printable (therefore false) */
int space_char(char c)
{
  if (c == ' ' || c == '\t' || c == '\0')
	    return 1;
  else
    return 0;
}

/* Return true (non-zero) if c is a non-whitespace 
   character (not tab or space).  
   Zero terminators are not printable (therefore false) */ 
int non_space_char(char c)
{
  if (c == ' ' || c == '\t' || c == '\0')
	    return 0;
  else
    return 1;
}

/* Returns a pointer to the first character of the next 
   space-separated word in zero-terminated str.  Return a zero pointer if 
   str does not contain any words. */
char *word_start(char *str)
{
  while(space_char(*str))
    *str++;
  return str;
}

/* Returns a pointer terminator char following *word */
char *word_terminator(char *word)
{
  while(space_char(*word))
    *word++;

  while(non_space_char(*word))
    *word++;
  
  return word;
}

/* Counts the number of words in the string argument. */
int count_words(char *str)
{
  int count = 0;
  char *p = str;

  if (*p == '\0')
    return 0;

  while (*p)
    {
      while(space_char(*p))
	*p++;

      for (; *p != '\0'; p++)
	if (*p == ' ' && *(p + 1) != ' ')
	  count++;
      count++;
    }
  return count;
}

/* Returns a fresly allocated new zero-terminated string 
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len)
{
  char* copy = (char*)malloc(len + 1);
  copy[len] = '\0';

  for (int i = 0; i < len; ++i)
    copy[i] = inStr[i];
  return copy;
}

/* Returns a freshly allocated zero-terminated vector of freshly allocated 
   space-separated tokens from zero-terminated str.

   For example, tokenize("hello world string") would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string" 
     tokens[3] = 0
*/
char **tokenize(char* str)
{
  short count = count_words(str);
  char **words = (char**)malloc((count + 1) * sizeof(char *));
  for (int i = 0; i < count; i++)
    {
      char *c = word_start(str);
      str = word_terminator(c);
      words[i] = copy_str(c, str - c);
    }
  words[count] = "0";
  return words;
}

/* Prints all tokens. */
void print_tokens(char **tokens)
{
  for (int i = 0; tokens[i - 1] != 0; i++)
	 printf("\ntokens[%d]: %s\n", i, tokens[i]);
}

/* Frees all tokens and the vector containing themx. */
void free_tokens(char **tokens)
{
  int i = 0;
  while(tokens[i] != 0)
    {
      free(tokens[i]);
      i++;
    }
  free(tokens);
}

#endif

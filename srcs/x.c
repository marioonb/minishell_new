		while (*s && *s != c)
		{
			if (*s == '\'' || *s == '"')
			{
				d = *s;
				s++;
				while (*s && *s != d)
					s++;
				if (*s != '\0')
					s++;
			}
			else
				s++;
		}

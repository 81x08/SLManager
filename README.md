# SLManager
Велосипед std::map

# Examples
```cpp
CData data;

data.Add(key, value);

if(data.IsKey(key))
{
	CVariant value = data.Get(key);

	e_types type = Value.GetType();

	switch(type)
	{
		case ET_INT:
		{
			cout << (int)Value;

			break;
		}
		case ET_DOUBLE:
		{
			cout << (double)Value;

			break;
		}
		case ET_STRING:
		{
			cout << (string)Value;

			break;
		}
	}
}

data.Remove(key);
```

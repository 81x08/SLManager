#ifndef _SLM_VARIANT_H_
#define _SLM_VARIANT_H_

namespace SLManager
{
	enum e_types
	{
		ET_NONE = 0,

		ET_INT,
		ET_DOUBLE,
		ET_STRING
	};

	class CVariant
	{
	private:
		struct s_variant
		{
			s_variant() : Type(ET_NONE), IntValue(0) {}
			s_variant(const e_types TYPE, const int Value) : Type(TYPE), IntValue(Value) {}
			s_variant(const e_types TYPE, const double Value) : Type(TYPE), DoubleValue(Value) {}
			s_variant(const e_types TYPE, const string &Value) : Type(TYPE), StringValue(new string(Value)) {}

			e_types Type;

			union
			{
				int IntValue;
				double DoubleValue;
				string *StringValue;
			};
		} m_Variant;

	public:
		CVariant() {}

		CVariant(const int IntValue) : m_Variant(ET_INT, IntValue) {}
		CVariant(const double DoubleValue) : m_Variant(ET_DOUBLE, DoubleValue) {}
		CVariant(const string &StringValue) : m_Variant(ET_STRING, StringValue) {}
		CVariant(const char *StringValue) : m_Variant(ET_STRING, (string)StringValue) {}

		CVariant(const CVariant &other)
		{
			*this = other;
		}

		~CVariant()
		{
			if(m_Variant.Type == ET_STRING)
			{
				delete m_Variant.StringValue;
			}
		}

        CVariant& operator= (const CVariant &other)
		{
            if(this != &other)
            {
                if(m_Variant.Type == ET_STRING)
				{
                    delete m_Variant.StringValue;
                }

				switch(other.m_Variant.Type)
				{
					case ET_STRING:
					{
						m_Variant.Type = ET_STRING;
						m_Variant.StringValue = new string(*(other.m_Variant.StringValue));

						break;
					}
					default:
					{
						memcpy(this, &other, sizeof(CVariant));
					}
				}
			}

            return *this;
        }

		operator int() const
		{
			switch(m_Variant.Type)
			{
				case ET_INT:
				{
					return m_Variant.IntValue;
				}
				case ET_DOUBLE:
				{
					return (int)m_Variant.DoubleValue;
				}
				default:
				{
					throw std::runtime_error("bad cast");
				}
			}
		}

		operator double() const
		{
			switch(m_Variant.Type)
			{
				case ET_INT:
				{
					return (double)m_Variant.IntValue;
				}
				case ET_DOUBLE:
				{
					return m_Variant.DoubleValue;
				}
				default:
				{
					throw std::runtime_error("bad cast");
				}
			}
		}

		operator string&() const
		{
			if(m_Variant.Type != ET_STRING)
			{
				throw std::runtime_error("bad cast");
			}

			return *m_Variant.StringValue;
		}

		const e_types GetType() const;
	};
}

#endif // _SLM_VARIANT_H_
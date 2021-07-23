#pragma once

using data_t = uint8_t;

class FinderSM
{
public:
	FinderSM()
	{
		init();
	}

	~FinderSM()
	{}

	void process_next(data_t& in)
	{
		switch (state)
		{
		case SkipZeros:
			if (in == 1)
			{
				state = CountFirstSubsequence;
				first_len = 1;
			}
			break;
		case CountFirstSubsequence:
			if (in == 0) 
			{
				state = CheckOneZero;
			}
			else if (in = 1)
			{
				++first_len;
			}
			break;
		case CheckOneZero:
			if (in == 0)
			{
				state = SkipZeros;
				first_len = 0;
			}
			else if (in = 1)
			{
				state = CountSecondSubsequence;
				second_len = 1;
			}
			break;
		case CountSecondSubsequence:
			if (in == 0)
			{
				state = CheckOneZero;
				if (first_len + second_len > max_len)
					max_len = first_len + second_len;
				first_len = second_len;
			}
			else if (in = 1)
			{
				++second_len;
			}

			break;
		default:
			break;
		}
	}

	void process_end()
	{
		if (state == CountSecondSubsequence)
		{
			if (first_len + second_len > max_len)
				max_len = first_len + second_len;
		}
	}

	void init()
	{
		state = FinderSMStates::SkipZeros;
		first_len = 0;
		second_len = 0;
		max_len = 0;
	}

	size_t get_max_length() const
	{
		return max_len;
	}

private:
	enum FinderSMStates
	{
		SkipZeros,
		CountFirstSubsequence,
		CheckOneZero,
		CountSecondSubsequence,
	};
	FinderSMStates state;
	size_t first_len, second_len, max_len;
};

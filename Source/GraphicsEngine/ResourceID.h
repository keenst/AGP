#pragma once
#include <cstdint>
class ResourceID
{
public:

	inline void SetLocalIndex(int aIndex)
	{
		myID = aIndex;
	}


	inline int GetLocalIndex() const 
	{
		return myID & 0xffffffff;
	}

	friend bool operator==(const ResourceID lhs, const ResourceID rhs);
	friend bool operator<(const ResourceID lhs, const ResourceID rhs);

	inline bool IsValid() const 
	{ 
		return myID != 0; 
	}

	inline bool IsNull() const
	{ 
		return myID == 0; 
	}

private:
	uint64_t myID = 0;
};

inline bool operator==(const ResourceID lhs, const ResourceID rhs) { return lhs.myID == rhs.myID; }
inline bool operator!=(const ResourceID lhs, const ResourceID rhs) { return !(lhs == rhs); }

inline bool operator<(const ResourceID lhs, const ResourceID rhs) { return lhs.myID < rhs.myID; }
inline bool operator>(const ResourceID lhs, const ResourceID rhs) { return rhs < lhs; }
inline bool operator<=(const ResourceID lhs, const ResourceID rhs) { return !(lhs > rhs); }
inline bool operator>=(const ResourceID lhs, const ResourceID rhs) { return !(lhs < rhs); }


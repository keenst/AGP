#pragma once
#include <cstdint>

constexpr uint64_t BUFFER_ID_CONSTANT_BIT = uint64_t(1) << 63;
constexpr uint64_t BUFFER_ID_VERTEX_BIT = uint64_t(1) << 62;
constexpr uint64_t BUFFER_ID_INDEX_BIT = uint64_t(1) << 61;
constexpr uint64_t BUFFER_ID_CPU_WRITE_BIT = uint64_t(1) << 60;
constexpr uint64_t BUFFER_ID_CPU_READ_BIT = uint64_t(1) << 59;

template<uint64_t Type>
struct ID
{
    uint64_t id;
    inline ID() = default;
    inline ID(uint64_t aID) :id(aID) {}


    bool operator==(const ID& rhs)
    {
        return id == rhs.id;
    }

    friend bool operator<(const ID& lhs, const ID& rhs);


    explicit operator bool() const
    {
        return IsValid();
    } 

    inline bool IsValid() const
    {
        return id != 0;
    }

    inline bool IsNull() const
    {
        return id == 0;
    }

    inline bool GetLocalIndex() const
    {
        return id & 0xffffffff;
    }

    inline uint64_t GetID() const
    {
        return id;
    }
};

template<uint64_t Type>
inline bool operator==(const ID<Type>& lhs, const ID<Type>& rhs)
{
    return lhs.id == rhs.id;
}

template<uint64_t Type>
bool operator!=(const ID<Type>& lhs, const ID<Type>& rhs) { return !(lhs == rhs); }

template<uint64_t Type>
bool operator<(const ID<Type>& lhs, const ID<Type>& rhs)
{
    return lhs.id < rhs.id;
}

template<uint64_t Type>
inline bool operator>(const ID<Type>& lhs, const ID<Type>& rhs) { return rhs < lhs; }
template<uint64_t Type>
inline bool operator<=(const ID<Type>& lhs, const ID<Type>& rhs) { return !(lhs > rhs); }
template<uint64_t Type>
inline bool operator>=(const ID<Type>& lhs, const ID<Type>& rhs) { return !(lhs < rhs); }


//horrible system I don't like it

using SamplerID = ID<0>;
using TextureID = ID<1>;
using RasterizerStateID = ID<2>;
using PipelineID = ID<3>;
using ShaderID = ID<4>;

//make a generic BufferID with bits masking the types?
using VertexBufferID = ID<5>;
using IndexBufferID = ID<6>;
using BufferID = ID<7>;
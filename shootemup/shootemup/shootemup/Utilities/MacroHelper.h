#pragma once

#define GenerateDynamicSingleton(class_t)         \
class_t* class_t::m_instance = nullptr;           \
                                                  \
void class_t::Create()                            \
{                                                 \
    if (m_instance == nullptr)                    \
        m_instance = new class_t();               \
}                                                 \
                                                  \
void class_t::Destroy()                           \
{                                                 \
    if (m_instance != nullptr)                    \
    {                                             \
        delete m_instance;                        \
        m_instance = nullptr;                     \
    }                                             \
}                                                 \
                                                  \
class_t & class_t::Instance()                     \
{                                                 \
    if (m_instance == nullptr)                    \
        Create();                                 \
    return *m_instance;                           \
}                                                 \
                                                  \
class_t::class_t(const class_t&) {}               \
class_t::class_t(class_t&&) noexcept {}           \
void class_t::operator = (const class_t&) {}      \
void class_t::operator = (class_t&&) noexcept {}  \

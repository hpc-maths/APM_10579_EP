#pragma once
#include "resource.hpp"

struct manager
{
    manager();
    ~manager();

    void print();
    static resource m_r;
};

static manager m;
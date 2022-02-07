#pragma once
#include "resource.hpp"

struct manager
{
    manager();
    ~manager();

    void print();
    resource& get_resource();
};

static manager m;
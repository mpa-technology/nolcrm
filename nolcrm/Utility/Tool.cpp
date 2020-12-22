/*
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/

#include "Tool.hpp"

bool subOverflow(const quint64 &a, const quint64 &b){

    const long long al = static_cast<long long>(a);
    const long long bl = static_cast<long long>(b);

    return al - bl < 0;
}

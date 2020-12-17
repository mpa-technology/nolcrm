#ifndef NOL_CRM_TOOL_HPP
#define NOL_CRM_TOOL_HPP
#include <numeric>
#include <QtGlobal>


template<typename T>
bool subOverflow(const T& a,const T& b){
    if((a < 0) && (a > std::numeric_limits<T>::max())+b)
        return false;
    return true;
}

template<typename T>
bool addOverflow(const T& a,const T& b){
    if((a < 0) && (a > std::numeric_limits<T>::max())-b)
        return false;
    return true;
}





#endif // NOL_CRM_TOOL_HPP

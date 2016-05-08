// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_GROUP_REF_HPP_
#define BOOST_PROCESS_DETAIL_WINDOWS_GROUP_REF_HPP_

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/windows/group_handle.hpp>
#include <boost/detail/winapi/process.hpp>
#include <boost/process/detail/windows/handler.hpp>

#include <iostream>

namespace boost { namespace process {

namespace detail { namespace windows {



struct group_ref : handler_base_ext
{
    ::boost::detail::winapi::HANDLE_ handle;

    explicit group_ref(::boost::detail::winapi::HANDLE_ h) :
                handle(h)
    {}

    template <class Executor>
    void on_setup(Executor& exec) const
    {
        //I can only enable this if the current process supports breakaways.
        if (in_group() && break_away_enabled(nullptr))
            exec.creation_flags  |= boost::detail::winapi::CREATE_BREAKAWAY_FROM_JOB_;
    }


    template <class Executor>
    void on_success(Executor& exec) const
    {
        if (!::boost::detail::winapi::AssignProcessToJobObject(handle, exec.proc_info.hProcess))
            throw_last_error("AssignProcessToJobObject() failed.");

    }

};

}}}}


#endif /* BOOST_PROCESS_DETAIL_WINDOWS_GROUP_HPP_ */
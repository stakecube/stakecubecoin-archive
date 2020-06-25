// Copyright (c) 2011-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2015-2018 The COLX developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_FINALLY_H
#define BITCOIN_FINALLY_H

#include <functional>
#include <exception>

/**
 * \brief Finalization pattern - call specified function on scope exit
*/
struct Finally
{
    typedef std::function<void ()> OnScopeExit;

    Finally(OnScopeExit fn) : fn_(fn)
    {
        if (!fn_)
            throw std::logic_error("Finally: invalid argument fn");
    }

    ~Finally()
    {
        bool exc = std::uncaught_exception();
        try {
            fn_();
        } catch (...) {
            if (exc)
                assert(false);
            else
                throw;
        }
    }

private:
    OnScopeExit fn_;
    Finally(const Finally&);
    Finally& operator=(const Finally&);
};

#endif // BITCOIN_FINALLY_H

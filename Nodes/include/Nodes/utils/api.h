//
// Created by Q on 24-11-2.
//

#pragma once

# if defined(NODE_DLLEXPORT)
#  define NODE_API __declspec(dllexport)
# elif defined(NODE_DLLIMPORT)
#  define NODE_API __declspec(dllimport)
# else
#  define NODE_API
# endif


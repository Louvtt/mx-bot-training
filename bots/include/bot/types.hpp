#ifndef _BOT_TYPES_HPP_
#define _BOT_TYPES_HPP_

/*
 * Functions types (with their macro)
 */

using update_func_t = void (*)();
#define REGISTER_UPDATE(func_name) update_func_t __update = &func_name;

#endif //_BOT_TYPES_HPP_
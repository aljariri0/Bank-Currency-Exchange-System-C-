#pragma once
#include <iostream>
#include "clsUser.h"

namespace GlobelUser {

	clsUser CurrentUser = clsUser::Find("", "");
}


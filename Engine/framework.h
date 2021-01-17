#pragma once

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.


// NOTE: 이렇게 쓰는게 맞는지 모르겠음.... 이렇게 작성하고 미리컴파일된헤더를 쓸때 pch.h를 include하고 아닐때 framework.h를 include하는 건가?
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Dalbit.h>
#include <iostream>
#include <string>
#include <fstream>
#include <optional>
#include <vector>
#include <filesystem>
#include <map>
#include <utility>
#include "Engine.h"



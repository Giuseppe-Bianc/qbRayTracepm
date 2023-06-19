#pragma once
#ifdef _MSC_VER
// Microsoft Visual C++ Compiler
#pragma warning(push)
#pragma warning(disable : 6386 6385)
#endif

#include <SDL.h>
#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <execution>
#include <format>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include <numbers>
#include <omp.h>
#include <optional>
#include <random>
#include <ranges>
#include <set>
#include <spdlog/cfg/env.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <sstream>
#include <stdexcept>
#include <string_view>
#include <unordered_set>
#include <vector>
// Restore warning levels.
#ifdef _MSC_VER
// Microsoft Visual C++ Compiler
#pragma warning(pop)
#endif

#define QBTRACE(...) SPDLOG_TRACE(__VA_ARGS__)
#define QBDEBUG(...) SPDLOG_DEBUG(__VA_ARGS__)
#define QBINFO(...) SPDLOG_INFO(__VA_ARGS__)
#define QBWARN(...) SPDLOG_WARN(__VA_ARGS__)
#define QBERROR(...) SPDLOG_ERROR(__VA_ARGS__)
#define QBCRITICAL(...) SPDLOG_CRITICAL(__VA_ARGS__)

#define C_ST(x) static_cast<std::size_t>(x)
#define C_CPCU32T(x) static_cast<const uint32_t *>(static_cast<const void *>(x))
#define C_UC(x) static_cast<unsigned char>(x)
#define C_32T(x) static_cast<int32_t>(x)
#define C_U32T(x) static_cast<uint32_t>(x)
#define C_U8T(c) static_cast<uint8_t>(x)
#define C_U8(x) static_cast<Uint8>(x)
#define C_I(x) static_cast<int>(x)
#define C_L(x) static_cast<long>(x)
#define C_D(x) static_cast<double>(x)
#define C_F(x) static_cast<float>(x)
#define POW2(p) (p) * (p)

#define QBSYSPAUSE()                                                                                                             \
    QBINFO("Press enter to exit...");                                                                                            \
    std::cin.ignore();

using ddvector = std::vector<std::vector<double>>;
static inline constexpr bool FWDTF = true;
static inline constexpr bool BCKTF = false;
static inline constexpr double NO_COLOR = 0.0;
static inline constexpr long NANOD = std::nano::den;
static inline constexpr long double pi = std::numbers::pi_v<long double>;
static inline constexpr long double twoPi = 2 * pi;
static inline constexpr long double halfPi = pi / 2;
// Dimensioni della finestra
// static inline constexpr double aspect_ratio = 16.0 / 9.0;
static inline constexpr double aspect_ratioW = 16.0;
static inline constexpr double aspect_ratioH = 9.0;
static inline constexpr int imageF = 80;
static inline constexpr int w = C_I(aspect_ratioW * imageF);
static inline constexpr int h = C_I(aspect_ratioH * imageF);
static inline constexpr std::size_t ST_w = C_ST(w);
static inline constexpr std::size_t ST_h = C_ST(h);
static inline constexpr double scale = 256.0;
static inline constexpr std::string_view windowTitle = "SDLPhysics";
static inline constexpr long long kNanoSecondsInMicrosecond = 1000;
static inline constexpr long long kNanoSecondsInMillisecond = 1000000;
static inline constexpr long long kNanoSecondsInSecond = 1000000000;
static inline constexpr long long kNanoSecondsInMinute = 60000000000;
static inline constexpr double invStHMinusOne = 1.0 / C_D(ST_h - 1);
static inline constexpr double invStWMinusOne = 1.0 / C_D(ST_w - 1);

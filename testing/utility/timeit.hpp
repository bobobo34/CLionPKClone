#pragma once
#ifndef TIMEIT_HPP
#define TIMEIT_HPP
#include <chrono>
#include <concepts>
#include <type_traits>
#include <functional>
#include <tuple>
#include <utility>

namespace timeit {
	template <typename T>
	concept time_interval = std::same_as<std::chrono::seconds, T> ||
		std::same_as<std::chrono::nanoseconds, T> ||
		std::same_as<std::chrono::microseconds, T> ||
		std::same_as<std::chrono::milliseconds, T> ||
		std::same_as<std::chrono::years, T> ||
		std::same_as<std::chrono::minutes, T> ||
		std::same_as<std::chrono::hours, T> ||
		std::same_as<std::chrono::days, T> ||
		std::same_as<std::chrono::weeks, T> ||
		std::same_as<std::chrono::months, T>;



	struct Timer {
		inline static void start() {
			begin = std::chrono::high_resolution_clock::now();
		}
		inline static void stop() {
			end = std::chrono::high_resolution_clock::now();
		}
		template<time_interval interval>
		inline static interval gettime() {
			return std::chrono::duration_cast<interval>(end - begin);
		}
	private:
		inline static std::chrono::high_resolution_clock::time_point begin;
		inline static std::chrono::high_resolution_clock::time_point end;
	};
	template<time_interval interval, typename ReturnType, typename... Arguments>
	auto TimeFunction(auto* func, std::tuple<Arguments...> parameters) {
		auto start = std::chrono::high_resolution_clock::now();
		if (std::is_same<ReturnType, void>::value) {
			std::apply(func, parameters);
			return std::tuple{ std::chrono::duration_cast<interval>(std::chrono::high_resolution_clock::now() - start), ReturnType{} };
		}
		else {
			return std::tuple{ std::chrono::duration_cast<interval>(std::chrono::high_resolution_clock::now() - start), std::apply(func, parameters) };
		}
	}
}
#endif
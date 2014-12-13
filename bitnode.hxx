#pragma once

namespace despairagus {
	namespace bitnode {
		template <typename A>
		class bitnode {
			namespace {
				template<typename B>
				using conref = const B &;

				using byte = unsigned char;
				using bit = bool;

				template <typename A>
				static inline void killPtr(A* &a) noexcept {
					if (a != nullptr) {
						delete a;
						a = nullptr;
					}
				}

				template <>
				static inline void killPtr(A) noexcept;

				template <>
				static inline void killPtr(bitnode<A>) noexcept;
			}

		public:
			inline explicit bitnode(void) noexcept : zero{nullptr}, one{nullptr}, data{nullptr} {}

			template <typename... A>
			explicit bitnode(A... a) = delete;

		private:
			bitnode* zero;
			bitnode* one;

			A* data;
		};
	}
}
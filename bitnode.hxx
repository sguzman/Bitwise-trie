#pragma once

namespace despairagus {
	namespace bitnode {
		template <typename A>
		class bitnode final {
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

			inline ~bitnode(void) noexcept {
				if (data != nullptr) {
					delete data;
				}
			}

			inline void dump(void) noexcept {
				bitnode<A>::killPtr<A>(data);
			}

			inline A* getData(void) const noexcept {
				return data;
			}

			inline void setData(conref<A> a) noexcept {
				this->dump();
				data = new A{a};
			}

			inline void setData(A* a) noexcept {
				this->dump();
				data = a;
			}

			inline void dumpZero(void) noexcept {
				bitnode<A>::killPtr<bitnode<A>>(zero);
			}

			inline bitnode<A>* getZero(void) const noexcept {
				return *zero;
			}

			inline void setZero(bitnode<A>* a) noexcept {
				this->dumpZero();
				data = a;
			}

			inline void dumpOne(void) noexcept {
				bitnode<A>::killPtr<bitnode<A>>(one);
			}

			inline bitnode<A>* getOne(void) const noexcept {
				return *one;
			}

			inline void setOne(bitnode<A>* a) noexcept {
				this->dumpOne();
				data = a;
			}

			inline void dumpAll(void) noexcept {
				this->dump();
				this->dumpZero();
				this->dumpOne();
			}

		private:
			bitnode<A>* zero;
			bitnode<A>* one;

			A* data;
		};
	}
}
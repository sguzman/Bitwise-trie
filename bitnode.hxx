#pragma once

namespace {
	namespace bitnodeNS {
		template <typename A>
		class bitnode final {
			template<typename B>
			using conref = const B &;

			using byte = unsigned char;
			using bit = bool;

			template <typename B>
			static inline void killPtr(B* &a) noexcept {
				if (a != nullptr) {
					delete a;
					a = nullptr;
				}
			}

		public:
			inline explicit bitnode(void) noexcept : zero{nullptr}, one{nullptr}, data{nullptr} {}

			template <typename... B>
			explicit bitnode(B...) = delete;

			template <typename B>
			explicit operator B (void) = delete;

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
				return zero;
			}

			inline void setZero(bitnode<A>* a) noexcept {
				this->dumpZero();
				zero = a;
			}

			inline void dumpOne(void) noexcept {
				bitnode<A>::killPtr<bitnode<A>>(one);
			}

			inline bitnode<A>* getOne(void) const noexcept {
				return one;
			}

			inline void setOne(bitnode<A>* a) noexcept {
				this->dumpOne();
				one = a;
			}

			inline void dumpAll(void) noexcept {
				this->dump();
				this->dumpZero();
				this->dumpOne();
			}

			inline bool isEmpty(void) const noexcept {
				return data == nullptr;
			}

			inline bool isNotEmpty(void) const noexcept {
				return !this->isEmpty();
			}

			inline bool haveZero(void) const noexcept {
				return zero != nullptr;
			}

			inline bool noZero(void) const noexcept {
				return !this->haveZero();
			}

			inline bool haveOne(void) const noexcept {
				return one != nullptr;
			}

			inline bool noOne(void) const noexcept {
				return !this->haveOne();
			}

			inline bool isBarren(void) const noexcept {
				return this->noZero() && this->noOne();
			}

			inline bool isNotBarren(void) const noexcept {
				return !this->isBarren();
			}

		private:
			bitnode<A>* zero;
			bitnode<A>* one;

			A* data;
		};
	}
}

#pragma once

#include <UTemplate/Typelist.h>

namespace Ubpa {
	namespace CmptTag {
		// LastFrame -> Write -> Newest

		template<typename Cmpt>
		class LastFrame {
		public:
			LastFrame(const Cmpt* cmpt) noexcept : cmpt{ cmpt } {}
			const Cmpt* get() const noexcept { return cmpt; }
			operator const Cmpt* () const noexcept { return cmpt; }
			const Cmpt* operator->() const noexcept { return cmpt; }
		private:
			const Cmpt* cmpt;
		};

		template<typename Cmpt>
		using Write = Cmpt*;

		template<typename Cmpt>
		using Newest = const Cmpt*;

		// Remove LastFrame, Write, Newest
		template<typename TagedCmpt>
		struct RemoveTag;
		template<typename TagedCmpt>
		using RemoveTag_t = typename RemoveTag<TagedCmpt>::type;

		template<typename TagedCmpt>
		struct IsLastFrame;
		template<typename TagedCmpt>
		static constexpr bool IsLastFrame_v = IsLastFrame<TagedCmpt>::value;

		template<typename TagedCmpt>
		struct IsWrite;
		template<typename TagedCmpt>
		static constexpr bool IsWrite_v = IsWrite<TagedCmpt>::value;

		template<typename TagedCmpt>
		struct IsNewest;
		template<typename TagedCmpt>
		static constexpr bool IsNewest_v = IsNewest<TagedCmpt>::value;

		template<typename TagedCmpt>
		struct IsTimePoint;
		template<typename TagedCmpt>
		static constexpr bool IsTimePoint_v = IsTimePoint<TagedCmpt>::value;

		template<typename ArgList>
		struct GetTimePointList : Filter<ArgList, IsTimePoint> {};
		template<typename ArgList>
		using GetTimePointList_t = typename GetTimePointList<ArgList>::type;

		template<typename ArgList>
		struct RemoveTimePoint : Filter<ArgList, Negate<IsTimePoint>::template Ttype> {};
		template<typename ArgList>
		using RemoveTimePoint_t = typename RemoveTimePoint<ArgList>::type;

		// ======================================================================

		template<typename... Cmpts>
		struct Before {
			using CmptList = TypeList<Cmpts...>;
		};
		template<typename TagedCmpt>
		struct IsBefore;
		template<typename TagedCmpt>
		static constexpr bool IsBefore_v = IsBefore<TagedCmpt>::value;

		template<typename... Cmpts>
		struct After {
			using CmptList = TypeList<Cmpts...>;
		};
		template<typename TagedCmpt>
		struct IsAfter;
		template<typename TagedCmpt>
		static constexpr bool IsAfter_v = IsAfter<TagedCmpt>::value;

		template<typename TagedCmpt>
		struct IsOrder : IValue<bool, IsBefore_v<TagedCmpt> || IsAfter_v<TagedCmpt>> {};
		template<typename TagedCmpt>
		static constexpr bool IsOrder_v = IsOrder<TagedCmpt>::value;

		template<typename ArgList>
		struct GetOrderList : Filter<ArgList, IsOrder> {};
		template<typename ArgList>
		using GetOrderList_t = typename GetOrderList<ArgList>::type;

		// ======================================================================

		template<typename... Cmpts>
		struct All {
			using CmptList = TypeList<Cmpts...>;
		};
		template<typename T>
		struct IsAll;
		template<typename T>
		static constexpr bool IsAll_v = IsAll<T>::value;
		template<typename ArgList>
		struct ConcatedAllList; // TypeList<AllCmpts...>
		template<typename ArgList>
		using ConcatedAllList_t = typename ConcatedAllList<ArgList>::type;

		template<typename... Cmpts>
		struct Any {
			using CmptList = TypeList<Cmpts...>;
		};
		template<typename T>
		struct IsAny;
		template<typename T>
		static constexpr bool IsAny_v = IsAny<T>::value;
		template<typename ArgList>
		struct ConcatedAnyList; // TypeList<AnyCmpts...>
		template<typename ArgList>
		using ConcatedAnyList_t = typename ConcatedAnyList<ArgList>::type;

		template<typename... Cmpts>
		struct None {
			using CmptList = TypeList<Cmpts...>;
		};
		template<typename T>
		struct IsNone;
		template<typename T>
		static constexpr bool IsNone_v = IsNone<T>::value;
		template<typename ArgList>
		struct ConcatedNoneList; // TypeList<NoneCmpts...>
		template<typename ArgList>
		using ConcatedNoneList_t = typename ConcatedNoneList<ArgList>::type;

		template<typename T>
		struct IsQuery : IValue<bool, IsAll_v<T> || IsAny_v<T> || IsNone_v<T>> {};
		template<typename T>
		static constexpr bool IsQuery_v = IsQuery<T>::value;
	}
}

#include "detail/CmptTag.inl"

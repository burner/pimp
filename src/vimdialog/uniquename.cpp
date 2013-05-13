#include <vimdialog/uniquename.hpp>

#include <unit.hpp>

std::string UniqueName::getName() {
	static std::string cur("aaaaaaaaaaaa");
	static size_t curPos = 0u;
	std::string ret = cur;
	if(cur[curPos] < 'z') {
		cur[curPos] = cur[curPos]+1;
	} else {
		++curPos;
		if(curPos >= cur.size()) {
			cur = std::string(curPos+1, 'a');
		}
	}

	return ret;
}

UNITTEST(UniqueName_getName_test1) {
	AS_EQ(UniqueName::getName(), "aaaaaaaaaaaa");
	AS_EQ(UniqueName::getName(), "baaaaaaaaaaa");
	for(size_t i = 0; i < 25; ++i) { UniqueName::getName(); }
	AS_EQ(UniqueName::getName(), "zbaaaaaaaaaa");
}

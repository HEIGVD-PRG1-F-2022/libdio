SHELL := /bin/bash
README_TAG := $(shell grep GIT_TAG README.md | sed -e "s/.* //")
CMAKE_VER := v$(shell grep project CMakeLists.txt | sed -e "s/.*VERSION \([^ ]*\) .*/\1/ ")

tag: check_tags
	if git tag | grep -q ${README_TAG}; then \
	  echo "Tag already exists"; \
	else \
	  git tag ${README_TAG}; \
	  git push --tags; \
	fi

check_tags:
	@if [[ ${README_TAG} != ${CMAKE_VER} ]]; then \
	  echo "README and CMakeLists.txt have different tags - please fix!"; \
	  exit 1; \
	fi

format:
	find . -name "*.cpp" -o -name "*.h" -o -name "*.tpp" | xargs clang-format -i

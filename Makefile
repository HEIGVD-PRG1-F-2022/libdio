tag:
	@README_TAG=$$( grep GIT_TAG README.md | sed -e "s/.* //" ); \
	if git tag | grep -q $$README_TAG; then \
	  echo "Tag already exists"; \
	else \
	  git tag $$README_TAG; \
	  git push --tags; \
	fi

format:
	find . -name "*.cpp" -o -name "*.h" -o -name "*.tpp" | xargs clang-format -i

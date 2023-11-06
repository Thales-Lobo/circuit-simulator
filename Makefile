public/adder.wasm: components/AdderWrapper/adder.mjs
components/AdderWrapper/adder.mjs: src_cpp/adder.cpp
	docker run \
		--rm \
		-v $(shell pwd)/src_cpp:/src \
		emscripten/emsdk \
		emcc --no-entry adder.cpp \
		-o adder.mjs \
		--pre-js locateFile.js \
		-s ENVIRONMENT='web' \
		-s EXPORT_NAME='createModule' \
		-s USE_ES6_IMPORT_META=0 \
		-s EXPORTED_FUNCTIONS='["_adder"]' \
		-s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]'  \
		-O3

	mv src_cpp/adder.mjs components/AdderWrapper/adder.mjs
	mv src_cpp/adder.wasm public/adder.wasm

.PHONY: clean
clean:
	rm public/adder.wasm components/AdderWrapper/adder.mjs
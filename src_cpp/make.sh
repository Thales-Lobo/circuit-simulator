MODULE_NAME=adder
OUTPUT_JS=adder_plumbing.js
OUTPUT_WASM=adder_plumbing.wasm

emcc ${MODULE_NAME}.cpp \
	-o $OUTPUT_JS \
	-g1 \
	-s WASM=1 \
	-s MODULARIZE=1 \
	-s EXPORT_ES6=1 \
	-s 'EXPORT_NAME="$MODULE_NAME"' \
	-s EXPORTED_RUNTIME_METHODS=['ccall','cwrap'] \
	-s 'ENVIRONMENT="web"'

    # disable eslint
rm $OUTPUT_JS
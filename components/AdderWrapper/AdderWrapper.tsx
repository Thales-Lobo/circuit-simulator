import { useEffect, useRef } from "react";
import createModule from "./adder.mjs";


const useAdder = () => {

    const adder = useRef<(a: number, b: number)=>number>(() => 0);


    useEffect(() => {        
        (createModule() as any).then((Module:any) => {
            adder.current = wrapAdder(Module);
        })
    }, []);

    return {
        adder: adder.current
    }
}

function wrapAdder(Module:any) {
    
    return function(a:number, b: number) {
        console.log(a, b)
        const result = Module.ccall(
            "adder",
            "number",
            ["number", "number"],
            [a, b]
        ) as number;

        // const adder = Module.cwrap(
        //     'adder',
        //     'number',
        //     ['number']
        // );
        // const result = adder(a, b);

        console.log(result)
        return result;
    }
}

export default useAdder;
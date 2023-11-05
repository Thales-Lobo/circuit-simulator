'use client';

// If used in Pages Router, is no need to add "use client"
import React, { useEffect, useRef, useState } from 'react';
import { Button, Input, Tooltip } from 'antd';

import dynamic from "next/dynamic";

interface CComponent {
  adder: (a:number, b:number) => number;
}


interface NumericInputProps {
  style: React.CSSProperties;
  value: string;
  placeholder?: string;
  onChange: (value: string) => void;
}

const formatNumber = (value: number) => new Intl.NumberFormat().format(value);

const NumericInput = (props: NumericInputProps) => {
  const { value, onChange } = props;

  const handleChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    const { value: inputValue } = e.target;
    const reg = /^-?\d*(\.\d*)?$/;
    if (reg.test(inputValue) || inputValue === '' || inputValue === '-') {
      onChange(inputValue);
    }
  };

  // '.' at the end or only '-' in the input box.
  const handleBlur = () => {
    let valueTemp = value;
    if (value.charAt(value.length - 1) === '.' || value === '-') {
      valueTemp = value.slice(0, -1);
    }
    onChange(valueTemp.replace(/0*(\d+)/, '$1'));
  };

  const title = value ? (
    <span className="numeric-input-title">{value !== '-' ? formatNumber(Number(value)) : '-'}</span>
  ) : (
    'Input a number'
  );

  return (
    <Tooltip trigger={['focus']} title={title} placement="topLeft" overlayClassName="numeric-input">
      <Input
        {...props}
        onChange={handleChange}
        onBlur={handleBlur}
        placeholder={props.placeholder}
        maxLength={16}
      />
    </Tooltip>
  );
};

const Home = () => {
  
  const module = useRef<CComponent | undefined>();
  const [value1, setValue1 ] = useState<string>('');
  const [value2, setValue2 ] = useState<string>('');

  const [sum, setSum] = useState<number | undefined>();
  
  const handleClick = () => {
    if(module.current) {
      setSum(module.current.adder(Number(value1), Number(value2)));
    }
  }
  
  useEffect(() => {
    const loadWasm = async () => {
      // @ts-ignore
      const wasmModule = await import('../src_cpp/adder_plumbing.wasm') as CComponent;
      module.current = wasmModule;
    }

    loadWasm();
  }, []);
  
  return (
    <div style={{margin: '20px', padding: '10px'}}>
      <div
        style={{
          display: 'flex',
          flexDirection: 'column',
          gap: '10px',
          width: '200px'
        }}
      >
        <NumericInput style={{width: '100%'}} placeholder='Primeiro número' value={value1} onChange={setValue1} />
        <NumericInput style={{width: '100%'}} placeholder='Segundo número' value={value2} onChange={setValue2} />

        <Button style={{flexGrow: 0}} onClick={handleClick} type="primary">Somar</Button>

        <p>Resultado: {sum}</p>
      </div>
    </div>
  )
};

export default Home;
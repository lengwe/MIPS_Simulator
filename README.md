# MIPS_Simulator

This is an Advanced Computer Architecure coursework. The full specification can be found in [here](https://github.com/m8pple/arch2-2019-cw).

## Simulator build and execution

To build the simulator, simply run the following command in root of the repository.

```
make simulator
```

This will then generate an excutable file called: `bin/mips_simulator`.

To run the simulator, use the existence of a Binary file, such as `./testbench/xxx.bin` as the input. For example,

```
bin/mips_simulator ./testbench/add1.mips.bin
```

## Testbench build and execution

To build the simulator, run the following command in root of the repository.

```
make testbench
```

This should result in an executable file called: `bin/mips_testbench`

To run the testbench on its own simulator, run the following command:

```
bin/mips_testbench  bin/mips_simulator
```

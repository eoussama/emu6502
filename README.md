# Emu 6502


## Description

Barebone emulator for the 6502 micro-processor for personal needs.

More on the 6502 at [www.6502.org](http://www.6502.org/users/obelisk/6502/).

The static library is insde the `src/core` directory.

## Installation

After cloning the repository, initialize the build directory:

```bash
./scripts/init.sh
```

Then, build the project:

```bash
./scripts/build.sh
```

## Usage

There is a sandbox environment that can be used to play around with the emulator inside the `src/sandbox` directory.

To run it, execute the following command:

```bash
./scripts/sandbox.sh
```

## Test

This project uses [Google Test](https://github.com/google/googletest) for testing.

To run the tests, execute the following command:

```bash
./scripts/test.sh
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
#pragma once
#include <cstdint>
#include <memory>
class Cartridge;
class PPU2C02;
class CPU6502;
class Bus
{
public:
	Bus();
	~Bus();
	void insert_cartridge(const std::shared_ptr<Cartridge>& cartridge);
	void reset();
	void clock();
	bool read(uint16_t addr, uint8_t &data, bool bReadOnly = false);
	bool write(uint16_t addr, uint8_t data);
	bool dma();

public:

	std::shared_ptr<CPU6502> cpu_;

	//the ppu exposes eight memory-mapped registers, $2000 through $2007,
	//but because they're incompletely decoded, they're mirrored in every 8 bytes from $2008 through $3FFF
	std::shared_ptr<PPU2C02> ppu_;		
	std::shared_ptr<Cartridge> cart_;

	uint8_t onboard_ram_[0x0800]; // 2k onboard ram(8k addr map to 2k).  //addr >= 0x0000 && addr <= 0x1FFF
	uint8_t controller_[2];	//controller.  addr >= 0x4016 && addr <= 0x4017
private:
	uint32_t total_cycles_ = 0;
	uint8_t controller_state_[2];

	//variables for DMA
	uint8_t dma_page_index_ = 0x00;
	uint8_t dma_inpage_addr_ = 0x00;
	uint8_t dma_data_on_transfer_ = 0x00;
	bool is_dma_mode_;
	uint32_t cycles_on_dma_;
};


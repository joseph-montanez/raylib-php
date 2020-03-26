<?php

namespace raylib;

/**
 * Class Wave
 * Handle .wav files
 * @package raylib
 *
 */
class Wave
{
    /**
     * Loads wave file.
     *
     * {@internal RLAPI Wave LoadWave(const char *fileName);}}
     *
     * @param string $fileName The location of the wave file
     */
    public function __construct(string $fileName)
    {
    }

    /**
     * Get the total number of samples
     *
     * @return int
     */
    public function getSampleCount(): int
    {
    }

    /**
     * Sets the total number of samples
     *
     * @param int $sampleCount
     */
    public function setSampleCount(int $sampleCount): void
    {
    }

    /**
     * Get the frequency (samples per second)
     *
     * @return int
     */
    public function getSampleRate(): int
    {
    }

    /**
     * Sets the frequency (samples per second)
     *
     * @param int $sampleRate
     */
    public function setSampleRate(int $sampleRate): void
    {
    }

    /**
     * Get the bit depth (bits per sample): 8, 16, 32 (24 not supported)
     *
     * @return int
     */
    public function getSampleSize(): int
    {
    }

    /**
     * Sets the bit depth (bits per sample): 8, 16, 32 (24 not supported)
     *
     * @param int $sampleSize
     */
    public function setSampleSize(int $sampleSize): void
    {
    }

    /**
     * Get the number of channels (1-mono, 2-stereo)
     *
     * @return int
     */
    public function getChannels(): int
    {
    }

    /**
     * Sets the number of channels (1-mono, 2-stereo)
     *
     * @param int $channels
     */
    public function setChannels(int $channels): void
    {
    }

    /**
     * Get the buffer data
     *
     * @return string
     */
    public function getData(): string
    {
    }

    /**
     * Sets the buffer data
     *
     * @param string $data
     */
    public function setData(string $data): void
    {
    }

    /**
     * Export wave data to file
     *
     * {@internal RLAPI void ExportWave(Wave wave, const char *fileName) }}
     *
     * @param string $fileName The filename to save the wave data to
     *
     */
    public function export(string $fileName): void
    {
    }

    /**
     * Export wave sample data to code (.h)
     *
     * {@internal RLAPI void ExportWaveAsCode(Wave wave, const char *fileName) }}
     *
     * @param string $fileName The filename to save the wave data to
     *
     */
    public function exportAsCode(string $fileName): void
    {
    }

    /**
     * Convert wave data to desired format
     *
     * {@internal RLAPI void WaveFormat(Wave *wave, int sampleRate, int sampleSize, int channels) }}
     *
     * @param int $sampleRate - Frequency (samples per second)
     * @param int $sampleSize - Bit depth (bits per sample): 8, 16, 32 (24 not supported)
     * @param int $channels - Number of channels (1-mono, 2-stereo)
     */
    public function format(int $sampleRate, int $sampleSize, int $channels): void
    {
    }

    /**
     * Copy a wave to a new wave
     *
     * {@internal RLAPI Wave WaveCopy(Wave wave) }}
     *
     */
    public function copy(): Wave
    {
    }

    /**
     * Crop a wave to defined samples range
     *
     * {@internal RLAPI void WaveCrop(Wave *wave, int initSample, int finalSample) }}
     *
     */
    public function crop(int $initSample, int $finalSample): Wave
    {
    }

    /**
     * Get samples data from wave as a floats array
     *
     * {@internal RLAPI float *GetWaveData(Wave wave) }}
     *
     * @return float[]
     */
    public function getDataArray(): array
    {
    }
}

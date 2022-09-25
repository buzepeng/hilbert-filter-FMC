#include "FMCImaging.cuh"

int main(){
    int NX=1001, NZ = 1001, WaveNum=2048, iWaveLength = 4002, WaveLength = 4000, row_tof=64, col_tof=1002001;
    int taps = 64;
    float sample_freq = 100, element_freq = 5, low_cut = ((element_freq - 3)*2)/sample_freq, high_cut = ((element_freq+3)*2)/sample_freq, MindB = -30;
    std::cout<<"Initialing..."<<std::endl;
    FmcImaging fmc_img(WaveNum, WaveLength, iWaveLength, row_tof, col_tof, NZ, NX);
    std::cout<<"Reading FMC..."<<std::endl;
    fmc_img.read_data_to_gpu("/home/hilbert/data/FMC_Data_YJBL_5L64_0p5_100MHz_4000.csv", fmc_img.d_offLineFmc, WaveNum, iWaveLength);
    std::cout<<"Reading TOF..."<<std::endl;
    fmc_img.read_data_to_gpu("/home/hilbert/data/TOF_Data_40_40_0p04Plane.csv", fmc_img.d_iTof, col_tof, row_tof);
    std::cout<<"Transposing TOF..."<<std::endl;
    fmc_img.transpose(fmc_img.d_iTof, row_tof, col_tof);
    std::cout<<"Generating bandpass filter..."<<std::endl;
    fmc_img.get_freq_filter(low_cut, high_cut, taps, fmc_img.d_H);

    auto start = system_clock::now();
    std::cout<<"Filtering..."<<std::endl;
    fmc_img.freq_domain_filtering(fmc_img.d_offLineFmc, fmc_img.d_f_offLineFmc, fmc_img.d_H);
    std::cout<<"Hilbert Transforming..."<<std::endl;
    fmc_img.hilbert_transform(fmc_img.d_f_offLineFmc, fmc_img.d_Hilbert);
    std::cout<<"Imaging..."<<std::endl;
    fmc_img.imaging(fmc_img.d_offLineFmc, fmc_img.d_iTof, fmc_img.d_f_offLineFmc, fmc_img.d_TfmImage, MindB);
    auto end   = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
cout <<  "花费了" 
     << double(duration.count()) * microseconds::period::num / microseconds::period::den 
     << "秒" << endl;
————————————————
版权声明：本文为CSDN博主「sicolex」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/u013390476/article/details/50209603
    std::cout<<"Saving result..."<<std::endl;
    fmc_img.save_result_to_txt("/home/hilbert/data/output_data.txt", fmc_img.d_TfmImage);
}
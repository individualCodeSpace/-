%%��ȡ���ݲ����㹦���ף���������%%
% ���� MAT �ļ�
loaded_data = load('BPSK_signal_data.mat');

% ��ȡ�ṹ������
data_array = loaded_data.data_array;

% ���ù����׼���Ĳ���
fs = 40e6; % ������Ϊ40M
window = hamming(512); % �������ڣ�����Ϊ512
noverlap = 256; % �ص���������Ϊ������һ��
power_sum = [];
% ���ù��������о�����,���֪©�����0.1ʱ����׼��̬�о�����Ϊ1.28
for i = 1:numel(data_array)
    Bpsk_Signal = data_array(i).data;
    if data_array(i).sig_per == 0
        [Pxx_1, f] = pwelch(Bpsk_Signal, window, noverlap, [], fs);
        Pxx_normalized_1 = Pxx_1 / sum(Pxx_1);
        power_spectrum_entropy_1 = -sum(Pxx_normalized_1 .* log2(Pxx_normalized_1));
        power_sum = [power_sum, power_spectrum_entropy_1];
    end 
end
H_noise = power_sum / numel(data_array(1).snr);

% ��ʼ��Ԥ��׼ȷ���ʹ�����
right_count = 0;
err_count = 0;

% �����ṹ�����鲢���㹦���׺͹�������
for i = 1:numel(data_array)
    rec_Bpsk_Signal = data_array(i).data;
    
    % ���㹦����
    [Pxx, f] = pwelch(rec_Bpsk_Signal, window, noverlap, [], fs);

    % ���㹦������
    Pxx_normalized = Pxx / sum(Pxx);
    power_spectrum_entropy = -sum(Pxx_normalized .* log2(Pxx_normalized));
    
    % ���ݹ��������о������ж��Ƿ�����ź�
    if power_spectrum_entropy < H_noise
        right_count = right_count + 1;
    else 
        err_count = err_count + 1;   
    end
    
    
    
    %{
    % ���ƹ�����ͼ
    figure;
    subplot(2, 1, 1);
    plot(f, 10*log10(Pxx));
    plot(f, Pxx);
    title(['Power Spectral Density - SNR: ', num2str(data_array(i).snr), ', Signal Percentage: ', num2str(data_array(i).sig_per)]);
    xlabel('Frequency (Hz)');
    ylabel('Power/Frequency (dB/Hz)');

    % ��ʾ��������
    subplot(2, 1, 2);
    bar(power_spectrum_entropy);
    title(['Power Spectral Entropy - SNR: ', num2str(data_array(i).snr), ', Signal Percentage: ', num2str(data_array(i).sig_per)]);
    xlabel('Entropy');
    ylabel('Value');
    %}
end
% ����������Ԥ��׼ȷ��������ȵĹ�ϵ��Ԥ��׼ȷ����ռ�ձȣ��źų��ȣ��Ĺ�ϵ
acc = (err_count / 11);
disp(acc)
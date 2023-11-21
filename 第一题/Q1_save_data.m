%%% �������źŴ洢���� %%%
% �����ṹ������
data_array = struct('snr', cell(1, numel(-20:2:10)*numel(0:0.1:0.9)), 'sig_per', cell(1, numel(-20:2:10)*numel(0:0.1:0.9)), 'data', cell(1, numel(-20:2:10)*numel(0:0.1:0.9)));

% ������
counter = 1;

for snr = -20:2:10
    for sig_per = 0:0.1:0.9
        rec_Bpsk_Signal = Bpsk_Signal_generater(10e6,1,snr,sig_per);
        data_array(counter).snr = snr;
        data_array(counter).sig_per = sig_per;
        data_array(counter).data = rec_Bpsk_Signal;
        counter = counter + 1;
    end
end

% ���ṹ�����鱣�浽�ļ�
save('BPSK_signal_data.mat', 'data_array');






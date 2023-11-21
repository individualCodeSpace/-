function Bpsk_Signal = Bpsk_Signal_generater(symbol_rate,bits_per_symbol,snr_dB,signal_percentage)

num_symbols = floor(256*signal_percentage); % Ҫ���͵ķ������������ı������������������1024��������ֻ��Ҫ256�����ż���
% ���������������
data = randi([0 1], 1, num_symbols * bits_per_symbol);

% BPSK����
symbols = 2 * data - 1;

% ����ʱ���źţ������źŷ��ŵ�ʱ�䲽���϶��ǲ����ʵĵ�����
t_signal = 0:1/symbol_rate:(num_symbols*bits_per_symbol/symbol_rate - 1/symbol_rate);

% ���ɵ����źţ�
bpsk_signal = symbols .* cos(2 * pi * symbol_rate * t_signal);

% �������ź�Ƭ�Σ�Ϊ0����
signal_front = floor(rand * (256 - num_symbols));
signal_back = 256 - num_symbols - signal_front;
bpsk_signal_combine = [zeros(1,signal_front),bpsk_signal,zeros(1,signal_back)];

% �ϲ����ڲ壬���������˲�����������Ϊ4�������źŲ����ʣ���ʵ�ֳ���1024���ź�
upsampled_signal = upsample(bpsk_signal_combine,4);

%%% ƽ���������˲��� %%%
rolloff = 0.35; % ����ϵ��
span = 10; % �˲����ķ���������
sps = 4; % ÿ�����ŵ�������
rcosine_filter = rcosdesign(rolloff, span, sps);

% ���ϲ�������źŽ����˲���ȥ��������ֵ����ĸ�Ƶ����
filtered_signal = filter(rcosine_filter, 1, upsampled_signal);


% ��Ӹ�˹����
noise_power = 10^(-snr_dB/10);
noise = sqrt(noise_power/2) * (randn(1, length(filtered_signal)) + 1i * randn(1, length(filtered_signal)));
received_signal = filtered_signal + noise;
Bpsk_Signal = received_signal;
%{
t = 0:1/symbol_rate:(length(filtered_signal)/symbol_rate - 1/symbol_rate);


% ��ʾ�����źźͽ����ź�
figure;

subplot(4,1,1);
plot(t_signal, bpsk_signal);
title('BPSK�����ź�');

subplot(4,1,2);
plot(t, filtered_signal);
title('BPSK�����ź�');

subplot(4,1,3);
plot(t, received_signal);
title('BPSK�����ź�');

subplot(4,1,4);
plot(t, real(received_signal), 'r');
hold on;
plot(t, imag(received_signal), 'b');
title('�����źţ���ɫ��ʵ������ɫ���鲿��');
legend('ʵ��', '�鲿');
%}
end

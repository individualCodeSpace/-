import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm

x = np.matrix([[0.0, 0.0, 0.0, 0.0, 0.0, 0.0]]).T
print(x, x.shape)
n=x.size # States

P = np.diag([100.0, 100.0, 10.0, 10.0, 1.0, 1.0])
print(P, P.shape)

fig = plt.figure(figsize=(6, 6))
im = plt.imshow(P, interpolation="none", cmap=plt.get_cmap('binary'))
plt.title('Initial Covariance Matrix $P$')
ylocs, ylabels = plt.yticks()
# set the locations of the yticks
plt.yticks(np.arange(7))
# set the locations and labels of the yticks
plt.yticks(np.arange(6),('$x$', '$y$', '$\dot x$', '$\dot y$', '$\ddot x$', '$\ddot y$'), fontsize=22)

xlocs, xlabels = plt.xticks()
# set the locations of the yticks
plt.xticks(np.arange(7))
# set the locations and labels of the yticks
plt.xticks(np.arange(6),('$x$', '$y$', '$\dot x$', '$\dot y$', '$\ddot x$', '$\ddot y$'), fontsize=22)

plt.xlim([-0.5,5.5])
plt.ylim([5.5, -0.5])

from mpl_toolkits.axes_grid1 import make_axes_locatable
divider = make_axes_locatable(plt.gca())
cax = divider.append_axes("right", "5%", pad="3%")
plt.colorbar(im, cax=cax)


plt.tight_layout()
plt.show()

dt = 0.1 # Time Step between Filter Steps

A = np.matrix([[1.0, 0.0, dt, 0.0, 1/2.0*dt**2, 0.0],
              [0.0, 1.0, 0.0, dt, 0.0, 1/2.0*dt**2],
              [0.0, 0.0, 1.0, 0.0, dt, 0.0],
              [0.0, 0.0, 0.0, 1.0, 0.0, dt],
              [0.0, 0.0, 0.0, 0.0, 1.0, 0.0],
              [0.0, 0.0, 0.0, 0.0, 0.0, 1.0]])
print(A, A.shape)

H = np.matrix([[1.0, 0.0, 0.0, 0.0, 0.0, 0.0],
               [0.0, 1.0, 0.0, 0.0, 0.0, 0.0],
               [0.0, 0.0, 0.0, 0.0, 1.0, 0.0],
              [0.0, 0.0, 0.0, 0.0, 0.0, 1.0]])
print(H, H.shape)

ra = 10.0**2   # Noise of Acceleration Measurement
rp = 100.0**2  # Noise of Position Measurement
R = np.matrix([[rp, 0.0, 0.0, 0.0],
               [0.0, rp, 0.0, 0.0],
               [0.0, 0.0, ra, 0.0],
               [0.0, 0.0, 0.0, ra]])
print(R, R.shape)

fig = plt.figure(figsize=(6, 6))
im = plt.imshow(R, interpolation="none", cmap=plt.get_cmap('binary'))
plt.title('Measurement Noise Covariance Matrix $R$')
ylocs, ylabels = plt.yticks()
# set the locations of the yticks
plt.yticks(np.arange(5))
# set the locations and labels of the yticks
plt.yticks(np.arange(4),('$x$', '$y$', '$\ddot x$', '$\ddot y$'), fontsize=22)

xlocs, xlabels = plt.xticks()
# set the locations of the yticks
plt.xticks(np.arange(5))
# set the locations and labels of the yticks
plt.xticks(np.arange(4),('$x$', '$y$', '$\ddot x$', '$\ddot y$'), fontsize=22)

plt.xlim([-0.5,3.5])
plt.ylim([3.5, -0.5])

from mpl_toolkits.axes_grid1 import make_axes_locatable
divider = make_axes_locatable(plt.gca())
cax = divider.append_axes("right", "5%", pad="3%")
plt.colorbar(im, cax=cax)

plt.tight_layout()
plt.show()

from sympy import Symbol, Matrix
from sympy.interactive import printing
printing.init_printing()
dts = Symbol('\Delta t')
Qs = Matrix([[0.5*dts**2],[0.5*dts**2],[dts],[dts],[1.0],[1.0]])
Qs*Qs.T

sa = 0.001
G = np.matrix([[1/2.0*dt**2],
               [1/2.0*dt**2],
               [dt],
               [dt],
               [1.0],
               [1.0]])
Q = G*G.T*sa**2

print(Q, Q.shape)

fig = plt.figure(figsize=(6, 6))
im = plt.imshow(Q, interpolation="none", cmap=plt.get_cmap('binary'))
plt.title('Process Noise Covariance Matrix $Q$')
ylocs, ylabels = plt.yticks()
# set the locations of the yticks
plt.yticks(np.arange(7))
# set the locations and labels of the yticks
plt.yticks(np.arange(6),('$x$', '$y$', '$\dot x$', '$\dot y$', '$\ddot x$', '$\ddot y$'), fontsize=22)

xlocs, xlabels = plt.xticks()
# set the locations of the yticks
plt.xticks(np.arange(7))
# set the locations and labels of the yticks
plt.xticks(np.arange(6),('$x$', '$y$', '$\dot x$', '$\dot y$', '$\ddot x$', '$\ddot y$'), fontsize=22)

plt.xlim([-0.5,5.5])
plt.ylim([5.5, -0.5])

from mpl_toolkits.axes_grid1 import make_axes_locatable
divider = make_axes_locatable(plt.gca())
cax = divider.append_axes("right", "5%", pad="3%")
plt.colorbar(im, cax=cax)

plt.tight_layout()
plt.show()


I = np.eye(n)
print(I, I.shape)

m = 500 # Measurements

sp= 1.0 # Sigma for position
px= 0.0 # x Position
py= 0.0 # y Position

mpx = np.array(px+sp*np.random.randn(m))
mpy = np.array(py+sp*np.random.randn(m))

# Generate GPS Trigger
GPS=np.ndarray(m,dtype='bool')
GPS[0]=True
# Less new position updates
for i in range(1,m):
    if i%10==0:
        GPS[i]=True
    else:
        mpx[i]=mpx[i-1]
        mpy[i]=mpy[i-1]
        GPS[i]=False

sa= 0.1 # Sigma for acceleration
ax= 0.0 # in X
ay= 0.0 # in Y

mx = np.array(ax+sa*np.random.randn(m))
my = np.array(ay+sa*np.random.randn(m))
measurements = np.vstack((mpx,mpy,mx,my))
print(measurements.shape)
def plot_m():
    fig = plt.figure(figsize=(16,9))
    plt.subplot(211)
    plt.step(range(m),mpx, label='$x$')
    plt.step(range(m),mpy, label='$y$')
    plt.ylabel(r'Position $m$')
    plt.title('Measurements')
    plt.ylim([-10, 10])
    plt.legend(loc='best',prop={'size':18})

    plt.subplot(212)
    plt.step(range(m),mx, label='$a_x$')
    plt.step(range(m),my, label='$a_y$')
    plt.ylabel(r'Acceleration $m/s^2$')
    plt.ylim([-1, 1])
    plt.legend(loc='best',prop={'size':18})

    plt.savefig('Kalman-Filter-CA-Measurements.png', dpi=72, transparent=True, bbox_inches='tight')
plot_m()

# Preallocation for Plotting
xt = []
yt = []
dxt = []
dyt = []
ddxt = []
ddyt = []
Zx = []
Zy = []
Px = []
Py = []
Pdx = []
Pdy = []
Pddx = []
Pddy = []
Kx = []
Ky = []
Kdx = []
Kdy = []
Kddx = []
Kddy = []

def savestates(x, Z, P, K):
    xt.append(float(x[0]))
    yt.append(float(x[1]))
    dxt.append(float(x[2]))
    dyt.append(float(x[3]))
    ddxt.append(float(x[4]))
    ddyt.append(float(x[5]))
    Zx.append(float(Z[0]))
    Zy.append(float(Z[1]))
    Px.append(float(P[0, 0]))
    Py.append(float(P[1, 1]))
    Pdx.append(float(P[2, 2]))
    Pdy.append(float(P[3, 3]))
    Pddx.append(float(P[4, 4]))
    Pddy.append(float(P[5, 5]))
    Kx.append(float(K[0, 0]))
    Ky.append(float(K[1, 0]))
    Kdx.append(float(K[2, 0]))
    Kdy.append(float(K[3, 0]))
    Kddx.append(float(K[4, 0]))
    Kddy.append(float(K[5, 0]))





for filterstep in range(m):

    # Time Update (Prediction)
    # ========================
    # Project the state ahead
    x = A * x

    # Project the error covariance ahead
    P = A * P * A.T + Q

    # Measurement Update (Correction)
    # ===============================
    # if there is a GPS Measurement
    if GPS[filterstep]:
        # Compute the Kalman Gain
        S = H * P * H.T + R
        K = (P * H.T) * np.linalg.pinv(S)

        # Update the estimate via z
        Z = measurements[:, filterstep].reshape(H.shape[0], 1)
        y = Z - (H * x)  # Innovation or Residual
        x = x + (K * y)

        # Update the error covariance
        P = (I - (K * H)) * P

    # Save states for Plotting
    savestates(x, Z, P, K)

def plot_P():
    fig = plt.figure(figsize=(16,9))
    plt.subplot(211)
    plt.plot(range(len(measurements[0])),Px, label='$x$')
    plt.plot(range(len(measurements[0])),Py, label='$y$')
    plt.title('Uncertainty (Elements from Matrix $P$)')
    plt.legend(loc='best',prop={'size':22})
    plt.subplot(212)
    plt.plot(range(len(measurements[0])),Pddx, label='$\ddot x$')
    plt.plot(range(len(measurements[0])),Pddy, label='$\ddot y$')

    plt.xlabel('Filter Step')
    plt.ylabel('')
    plt.legend(loc='best',prop={'size':22})
plot_P()

def plot_P2():
    fig = plt.figure(figsize=(6, 6))
    im = plt.imshow(P, interpolation="none", cmap=plt.get_cmap('binary'))
    plt.title('Covariance Matrix $P$ (after %i Filter Steps)' % (m))
    ylocs, ylabels = plt.yticks()
    # set the locations of the yticks
    plt.yticks(np.arange(7))
    # set the locations and labels of the yticks
    plt.yticks(np.arange(6),('$x$', '$y$', '$\dot x$', '$\dot y$', '$\ddot x$', '$\ddot y$'), fontsize=22)

    xlocs, xlabels = plt.xticks()
    # set the locations of the yticks
    plt.xticks(np.arange(7))
    # set the locations and labels of the yticks
    plt.xticks(np.arange(6),('$x$', '$y$', '$\dot x$', '$\dot y$', '$\ddot x$', '$\ddot y$'), fontsize=22)

    plt.xlim([-0.5,5.5])
    plt.ylim([5.5, -0.5])

    from mpl_toolkits.axes_grid1 import make_axes_locatable
    divider = make_axes_locatable(plt.gca())
    cax = divider.append_axes("right", "5%", pad="3%")
    plt.colorbar(im, cax=cax)


    plt.tight_layout()
    plt.savefig('Kalman-Filter-CA-CovarianceMatrix.png', dpi=72, transparent=True, bbox_inches='tight')
plot_P2()

def plot_K():
    fig = plt.figure(figsize=(16,9))
    plt.plot(range(len(measurements[0])),Kx, label='Kalman Gain for $x$')
    plt.plot(range(len(measurements[0])),Ky, label='Kalman Gain for $y$')
    plt.plot(range(len(measurements[0])),Kdx, label='Kalman Gain for $\dot x$')
    plt.plot(range(len(measurements[0])),Kdy, label='Kalman Gain for $\dot y$')
    plt.plot(range(len(measurements[0])),Kddx, label='Kalman Gain for $\ddot x$')
    plt.plot(range(len(measurements[0])),Kddy, label='Kalman Gain for $\ddot y$')

    plt.xlabel('Filter Step')
    plt.ylabel('')
    plt.title('Kalman Gain (the lower, the more the measurement fullfill the prediction)')
    plt.legend(loc='best',prop={'size':18})
plot_K()


def plot_x():
    fig = plt.figure(figsize=(16, 16))

    plt.subplot(311)
    plt.step(range(len(measurements[0])), ddxt, label='$\ddot x$')
    plt.step(range(len(measurements[0])), ddyt, label='$\ddot y$')

    plt.title('Estimate (Elements from State Vector $x$)')
    plt.legend(loc='best', prop={'size': 22})
    plt.ylabel(r'Acceleration $m/s^2$')
    plt.ylim([-.1, .1])

    plt.subplot(312)
    plt.step(range(len(measurements[0])), dxt, label='$\dot x$')
    plt.step(range(len(measurements[0])), dyt, label='$\dot y$')

    plt.ylabel('')
    plt.legend(loc='best', prop={'size': 22})
    plt.ylabel(r'Velocity $m/s$')
    plt.ylim([-1, 1])

    plt.subplot(313)
    plt.step(range(len(measurements[0])), xt, label='$x$')
    plt.step(range(len(measurements[0])), yt, label='$y$')

    plt.xlabel('Filter Step')
    plt.ylabel('')
    plt.legend(loc='best', prop={'size': 22})
    plt.ylabel(r'Position $m$')
    plt.ylim([-1, 1])

    plt.savefig('Kalman-Filter-CA-StateEstimated.png', dpi=72, transparent=True, bbox_inches='tight')
plot_x()


def plot_xy():

    fig = plt.figure(figsize=(16,16))
    plt.plot(xt,yt, label='State',alpha=0.5)
    plt.scatter(xt[0],yt[0], s=100, label='Start', c='g')
    plt.scatter(xt[-1],yt[-1], s=100, label='Goal', c='r')

    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('Position')
    plt.legend(loc='best')
    plt.xlim([-5, 5])
    plt.ylim([-5, 5])
    plt.savefig('Kalman-Filter-CA-Position.png', dpi=72, transparent=True, bbox_inches='tight')
plot_xy()

dist=np.cumsum(np.sqrt(np.diff(xt)**2 + np.diff(yt)**2))
print('Your drifted %dm from origin.' % dist[-1])
from options import Options
from solvers import create_solver

if __name__ == '__main__':
    opt = Options().parse()
    #引入配置文件，并在这里读入参数
    solver = create_solver(opt)
    #利用配置创建求解器
    solver.run_solver()
    #运行求解器

    print('[THE END]')
    #结束
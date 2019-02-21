import logging
import time
import angr

target = "state_machine"

file_handler = logging.FileHandler(
    '%s_%s.log' % (target, time.strftime('%Y%m%d%H%M%S')))
formatter = logging.Formatter(
    '%(levelname)s | %(asctime)s | %(name)s | %(message)s')
file_handler.setFormatter(formatter)

logger = logging.getLogger()
logger.addHandler(file_handler)
logger.setLevel(logging.INFO)

def main():
    p = angr.Project("./" + target)
    s = p.factory.entry_state()
    simgr = p.factory.simgr(s)

    simgr.explore(find=lambda s: b"vulnerable code" in s.posix.dumps(1))

    logger.warning("vulnerable path found")


if __name__ == "__main__":
    main()
